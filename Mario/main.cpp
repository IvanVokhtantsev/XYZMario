#include <SFML/Graphics.hpp>
#include <string>

// Тип текстуры тайла. Нам это нужно чтобы превратить символы из карты во что-то читаемое
enum class ETileTextureType
{
    Empty,
    Ground
};

// Тип коллизии тайла. Коллизия это препятствие
enum class ETileCollisionType
{
    NoCollision,
    Collision
};

// Структура для описания тайла. Она нужна чтобы перевести символ из описания нашей карты в полностью понятный объект
struct Tile
{
    ETileTextureType textureType;
    ETileCollisionType collisionType;
};

// Структура для игровой карты
// Содержит информацию обо всех тайлах
struct Level
{
    std::vector<std::vector<Tile>> tiles;
};

// Описатель игровой карты. По сути редактор на минималках
struct LevelDescriptor
{
    std::vector<std::vector<char>> levelSymbols;
};

Level CreateLevel(const LevelDescriptor& levelDescriptor)
{
    Level level;
    
    for(int i = 0; i < levelDescriptor.levelSymbols.size(); ++i)
    {
        // Добавляем новый элемент в вектор. Это будет другой пустой вектор. аргумент {} превращается в std::vector<Tile>
        // Почитать об конвертации {} в объект можно тут https://en.cppreference.com/w/cpp/language/list_initialization
        level.tiles.push_back({});
        for(int j = 0; j < levelDescriptor.levelSymbols[i].size(); ++j)
        {
            Tile tile;
            // В зависимости от символа инициализируем тайл
            if(levelDescriptor.levelSymbols[i][j] == 'B')
            {
                tile.textureType = ETileTextureType::Ground;
                tile.collisionType = ETileCollisionType::Collision;
            }
            else if(levelDescriptor.levelSymbols[i][j] == 'S')
            {
                tile.textureType = ETileTextureType::Empty;
                tile.collisionType = ETileCollisionType::NoCollision;
            }

            // Добавляем тайл в карту
            level.tiles[i].push_back(tile);
        }
    }

    return level;
}

enum class EOrientaion
{
    Horizontal,
    Vertical
};

/*
 * Функция рассчитывает коллизию объекта с картой
 * Возвращает новое положение объекта после коллизии
 */
sf::Vector2f HandleCollision(
    const sf::FloatRect& objectRect/*положение и размеры объекта для которого считаем коллизию*/,
    const sf::Vector2f& objectVelocity /*скорость и направление движения объекта*/,
    const Level& level /*карта с тайлами*/,
    EOrientaion orientation /*ориентация коллизии. Горизонтальная или вертикальная*/,
    const sf::Vector2f& tileSize /*размер тайла*/)
{
    // Находим индексы тайлов в которых сейчас находится наш объект для которого мы считаем коллизию

    //Тайлы по X
    const int xLeftTile = objectRect.left / tileSize.x;
    const int xRightTile = (objectRect.left + objectRect.width) / tileSize.x;

    //Тайлы по Y
    const int yTopTile = objectRect.top / tileSize.y;
    const int yBottomTile = (objectRect.top + objectRect.height) / tileSize.y;

    for(int i = yTopTile; i < yBottomTile; ++i)
    {
        for(int j = xLeftTile; j <= xRightTile; ++j)
        {
            // Тайл с которым сейчас обрабатываем коллизию
            const Tile& tile = level.tiles[i][j];
            const sf::Vector2f tilePosition = sf::Vector2f(j * tileSize.x, i * tileSize.y);
            
            if(tile.collisionType == ETileCollisionType::Collision)
            {
                // Если коллизия горизонтальная, то смотрим на движение по оси X    
                if(orientation == EOrientaion::Horizontal)
                {
                    // Если объект двигается влево, то сдвигаем его вправо
                    if(objectVelocity.x < 0)
                    {
                        // Берём позицию тайла с коллизией и сдвигаем персонажа на правый тайл относительно тайла с коллизией
                        // Для этого мы берем координату тайла с коолизией и прибавляем размер этого тайла чтобы перескочить на правый тайл
                        return sf::Vector2f(tilePosition.x + tileSize.x, objectRect.top);
                    }
                    else
                    {
                        return sf::Vector2f(tilePosition.x - objectRect.width, objectRect.top);
                    }
                }
            }
        }
    }
    //Получаем позицию объекта из структуры Rect
    return objectRect.getPosition();
}


int main()
{
    LevelDescriptor levelDescriptor;
    levelDescriptor.levelSymbols =
        {
        {'B', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'B'}, // level[0]. Чтобы получить 3 нужно level[0][1]
        {'B', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'B'},  // level[1]. Чтобы получить 4 нужно level[1][2]
        {'B', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'B'},
        {'B', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'B'},
        {'B', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'B'},
        {'B', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'B'},
        {'B', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'B'},
        {'B', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'B'},
        {'B', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'B'},
        {'B', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'B'},
        {'B', 'S', 'S', 'B', 'S', 'S', 'B', 'S', 'B', 'S', 'S', 'B', 'S', 'S', 'S', 'B'},
        {'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B'}
        };

    Level level = CreateLevel(levelDescriptor);
    
    // Размер тайла внутри текстуры
    const sf::Vector2f textureTileSize(16.f, 16.f);
    
    // Глобальный скейл для всех спрайтов в игре. Т.к. изначально в текстуре они слишком маленькие
    const sf::Vector2f drawScale(3.f, 3.f);

    const sf::Vector2f tileSize(textureTileSize.x * drawScale.x, textureTileSize.y * drawScale.y);
    
    // Гравитация в игре. То с какой скоростью объекты будут падать вниз
    const float gravity = -2.f;
    
    // Создание основного игрового окна. С размером 800*600
    sf::RenderWindow window(sf::VideoMode(800 , 600), "Mario");

    // Расположение земли по координате Y. Высота земли = 200. Располагается внизу окна, поэтому для расчета положенеия земли мы используем размер окна
    const float groundTop = window.getSize().y - 70.f;
    
    // Загружаем текстуру земли из отдельного файла
    sf::Texture groundTexture;
    groundTexture.loadFromFile("Resources/Ground.png");
    // Создаем спрайт для отрисовки земли в нужном положении
    sf::Sprite groundSprite;
    groundSprite.setTexture(groundTexture);
    groundSprite.setPosition(0.f, groundTop);
    
    // Текстура с тайлсетом
    sf::Texture tileSetTexture;
    // Загрузка текстуры из файла
    tileSetTexture.loadFromFile("Resources/TileSet.png");

    const sf::Vector2f playerSize = textureTileSize;
    // Спрайт игрока. Спрайт это часть текстуры с указанием координат в текстуре
    // Спрайт не принимает участие в расчете игровой логики. Он нужен только для отрисовки
    sf::Sprite playerSprite;
    // Загружаем текстуру в спрайт
    playerSprite.setTexture(tileSetTexture);
    // Указываем какую часть текстуры будет использовать спрайт
    playerSprite.setTextureRect(sf::IntRect(117, 507, playerSize.x, playerSize.y));
    // Задаём скейл спрайту чтобы его увеличить
    playerSprite.setScale(drawScale);
    
    // Создание переменной для хранения размера и положения игрока
    sf::FloatRect playerRect(100.f, 400.f, playerSize.x * drawScale.x, playerSize.y * drawScale.y);

    // Текущее ускорение игрока. Показывает в какую сторону и на сколько быстро двигается игрок
    sf::Vector2f playerVelocity(0.f, 0.f);
    // Скорость игрока. Безразмерная величина. Указывает как быстро может двигаться игрок
    float playerSpeed = 220.f;

    // Скорость прыжка игрока аналогично playerSpeed
    float playerJumpSpeed = 500.f;
    // Переменная которая указывает находится ли игрок на земле. Это нужно для опеределия возможности прыжка
    bool bIsPlayerOnGround = false;

    // Используется для подсчета времени обработки игрового цикла
    sf::Clock clock;
    
    // Основной цикл игры. Происходит пока окно не закрыто
    while (window.isOpen())
    {
        // Остановка выполнения программы на какое-то время. Чтобы детерминировать время обработки игрового цикла, т.к. оно очень маленькое
        sf::sleep(sf::seconds(0.001f));
        
        // Получаем время которое прошло с момента предыдущего обновления игрового цикла
        float clockDeltaSeconds = clock.getElapsedTime().asSeconds();
        // Сбрасываем счетчик времени. Чтобы в начале следующего цикла получить новое актуальное время
        clock.restart();
        
        // Опрос окна о событиях
        sf::Event event;
        // Опрашиваем все события которые произошли в окне с момента его последней отрисовки
        while (window.pollEvent(event))
        {
            // Если было вызвано событие Закрыть, то закрываем окно
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Space)
                {
                    // Если нажали кнопку прыжка и игрок на земле, то запускаем логику прыжка
                    if(bIsPlayerOnGround)
                    {
                        bIsPlayerOnGround = false;
                        playerVelocity.y = playerJumpSpeed * clockDeltaSeconds;
                    }
                }
            }
        }
        // Обработка инпута с кнопок
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            playerVelocity.x = -playerSpeed * clockDeltaSeconds;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            playerVelocity.x = playerSpeed * clockDeltaSeconds;
        }

        // Основной блок обработки игровой логики
        {
            // На игрока постоянно оказывает влияние гравитация и тянет его вниз
            // Во время прыжка она будет всегда замедлять прыжок пока игрок не начнет двигаться вниз
            playerVelocity.y += gravity * clockDeltaSeconds;
            
            playerRect.left += playerVelocity.x;
            playerRect.left = HandleCollision(playerRect, playerVelocity, level, EOrientaion::Horizontal, tileSize).x;
            
            playerRect.top -= playerVelocity.y;

            // Определяем приземлился ли игрок на землю
            // Для этого сравниваем его нижнюю координату с землей
            // Если нижняя координата ниже земли, то считаем что игрок на земле и не даём ему упасть ниже
            const float playerRectBottom = playerRect.top + playerRect.height; 
            if(playerRectBottom > groundTop)
            {
                bIsPlayerOnGround = true;
                playerVelocity.y = 0.f;
                playerRect.top = groundTop - playerRect.height;
            }
            
            playerVelocity.x = 0.f;
        }

        // Блок отрисовки окна
        {
            // Очищаем окно от предыдущих изображений
            window.clear();

            // Отрисовываем новые данные в окне,
            //window.draw(groundSprite);
            
            for(int i = 0; i < level.tiles.size(); ++i)
            {
                for(int j = 0; j < level.tiles[i].size(); ++j)
                {
                    const Tile& tile = level.tiles[i][j];
                    
                    sf::RectangleShape tileRect;
                    tileRect.setPosition(tileSize.x * j, tileSize.y * i);
                    tileRect.setSize(tileSize);
                    if(tile.textureType == ETileTextureType::Ground)
                    {
                        tileRect.setFillColor(sf::Color::Red);
                    }
                    else if(tile.textureType == ETileTextureType::Empty)
                    {
                        tileRect.setFillColor(sf::Color::Blue);
                    }
                    window.draw(tileRect);
                }
            }
            
            playerSprite.setPosition(playerRect.left, playerRect.top);
            window.draw(playerSprite);
            // Выводим отрисованное на экран
            window.display();    
        }
    }

    return 0;
}