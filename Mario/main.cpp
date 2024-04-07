#include "GameLogic.h"

int main()
{
    // Размер тайла внутри текстуры
    const sf::Vector2i textureTileSize(16.f, 16.f);
    
    // Глобальный скейл для всех спрайтов в игре. Т.к. изначально в текстуре они слишком маленькие
    const sf::Vector2f drawScale(3.f, 3.f);

    const sf::Vector2f tileSize(textureTileSize.x * drawScale.x, textureTileSize.y * drawScale.y);
    
    // Гравитация в игре. То с какой скоростью объекты будут падать вниз
    const float gravity = -700.f;
    
    // Создание основного игрового окна. С размером 800*600
    sf::RenderWindow window(sf::VideoMode(800 , 600), "Mario");
    
    // Текстура с тайлсетом
    sf::Texture tileSetTexture;
    // Загрузка текстуры из файла
    tileSetTexture.loadFromFile("Resources/TileSet.png");

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
    levelDescriptor.tileSetTexture = tileSetTexture;
    
    levelDescriptor.tileTextureTypeToTextureRect[ETileTextureType::Ground] = sf::IntRect(373, 102, textureTileSize.x, textureTileSize.y);
    levelDescriptor.tileTextureTypeToTextureRect[ETileTextureType::Empty] = sf::IntRect(274, 365, textureTileSize.x, textureTileSize.y);

    Level level = CreateLevel(levelDescriptor, drawScale);

    Player player;
  
    // Загружаем текстуру в спрайт
    player.playerSprite.setTexture(tileSetTexture);
    // Указываем какую часть текстуры будет использовать спрайт
    player.playerSprite.setTextureRect(sf::IntRect(117, 507, textureTileSize.x, textureTileSize.y));
    // Задаём скейл спрайту чтобы его увеличить
    player.playerSprite.setScale(drawScale);
    
    // Создание переменной для хранения размера и положения игрока
    player.playerRect = sf::FloatRect(80.f, 450.f, textureTileSize.x * drawScale.x, textureTileSize.y * drawScale.y);
    
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
            HandleWindowsEvent(event, player);
        }

        HandleInput(player);

        UpdateGame(player, level, gravity, clockDeltaSeconds, tileSize);

        DrawGame(window, level, player, tileSize);
    }

    return 0;
}