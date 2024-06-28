#include "GameLogic.h"


int main()
{   
    // Размер тайла внутри текстуры
    const sf::Vector2i textureTileSize(16.f, 16.f);
    
    // Глобальный скейл для всех спрайтов в игре. Т.к. изначально в текстуре они слишком маленькие
    const sf::Vector2f drawScale(3.f, 3.f);

    const sf::Vector2f tileSize(textureTileSize.x * drawScale.x, textureTileSize.y * drawScale.y);
    
    // Создание основного игрового окна. С размером 800*600
    sf::RenderWindow window(sf::VideoMode(1200 , 600), "Mario");
    
    // Текстура с тайлсетом
    sf::Texture tileSetTexture;
    // Загрузка текстуры из файла
    tileSetTexture.loadFromFile("Resources/TileSet.png");

    LevelDescriptor levelDescriptor;
    levelDescriptor.levelSymbols =
        {
        /* 0*/{'B', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'B', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'B'}, // level[0]. Чтобы получить 3 нужно level[0][1]
        /* 1*/{'B', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'B'},  // level[1]. Чтобы получить 4 нужно level[1][2]
        /* 2*/{'B', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'B'},
        /* 3*/{'B', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'B'},
        /* 4*/{'B', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'B'},
        /* 5*/{'B', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'B'},
        /* 6*/{'B', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'B'},
        /* 7*/{'B', 'S', 'S', 'S', 'B', 'B', 'B', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'B'},
        /* 8*/{'B', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'B'},
        /* 9*/{'B', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'B', 'S', 'S', 'S', 'S', 'S', 'S', 'B'},
        /*10*/{'B', 'S', 'S', 'B', 'S', 'S', 'S', 'S', 'B', 'S', 'S', 'S', 'S', 'B', 'B', 'S', 'B', 'S', 'S', 'S', 'S', 'B', 'B', 'S', 'S', 'S', 'B', 'S', 'S', 'B'},
        /*11*/{'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B'}
        };
    levelDescriptor.tileSetTexture = tileSetTexture;
    
    levelDescriptor.tileTextureTypeToTextureRect[ETileTextureType::Ground] = sf::IntRect(373, 102, textureTileSize.x, textureTileSize.y);
    levelDescriptor.tileTextureTypeToTextureRect[ETileTextureType::Empty] = sf::IntRect(274, 365, textureTileSize.x, textureTileSize.y);

    sf::Font font;
    font.loadFromFile("Resources/DefaultFont.ttf");
    
    // Основной цикл приложения. Происходит пока окно не закрыто
    while (window.isOpen())
    {
        World world;

        world.renderWindow = &window;
        
        world.scoreText.setFont(font);
        world.scoreText.setCharacterSize(18);
        world.scoreText.setPosition(50.f,50.f);
        world.scoreText.setFillColor(sf::Color::White);
        world.scoreText.setStyle(sf::Text::Style::Bold);
    
        world.level = CreateLevel(world, levelDescriptor, drawScale, tileSize);

        {
            world.player = new Player;
            world.player->world = &world;
            world.objects.push_back(world.player);
            
            // Загружаем текстуру в спрайт
            world.player->sprite.setTexture(tileSetTexture);
            // Указываем какую часть текстуры будет использовать спрайт
            world.player->sprite.setTextureRect(sf::IntRect(117, 507, textureTileSize.x, textureTileSize.y));
            // Задаём скейл спрайту чтобы его увеличить
            world.player->sprite.setScale(drawScale);

            world.player->sprite.setOrigin(textureTileSize.x / 2.f, textureTileSize.y / 2.f);

            // Создание переменной для хранения размера и положения игрока
            world.player->rect = sf::FloatRect(80.f, 450.f, textureTileSize.x * drawScale.x, textureTileSize.y * drawScale.y);

            // Анимация бега
            {
                world.player->walkAnimation.texture = tileSetTexture;
                world.player->walkAnimation.speed = 7.f;
                world.player->walkAnimation.frames.push_back(sf::IntRect(84, 507, textureTileSize.x, textureTileSize.y));
                world.player->walkAnimation.frames.push_back(sf::IntRect(99, 507, textureTileSize.x, textureTileSize.y));
                world.player->walkAnimation.frames.push_back(sf::IntRect(117, 507, textureTileSize.x, textureTileSize.y));
            }

            {
                world.player->idleAnimation.texture = tileSetTexture;
                world.player->idleAnimation.speed = 0.f;
                world.player->idleAnimation.frames.push_back(sf::IntRect(23, 507, textureTileSize.x, textureTileSize.y));
            }

            {
                world.player->jumpUpAnimation.texture = tileSetTexture;
                world.player->jumpUpAnimation.speed = 0.f;
                world.player->jumpUpAnimation.frames.push_back(sf::IntRect(139, 507, textureTileSize.x, textureTileSize.y));
            }
            {
                world.player->jumpDownAnimation.texture = tileSetTexture;
                world.player->jumpDownAnimation.speed = 7.f;
                world.player->jumpDownAnimation.frames.push_back(sf::IntRect(68, 528, textureTileSize.x, textureTileSize.y));
                world.player->jumpDownAnimation.frames.push_back(sf::IntRect(90, 528, textureTileSize.x, textureTileSize.y));
                world.player->jumpDownAnimation.frames.push_back(sf::IntRect(113, 528, textureTileSize.x, textureTileSize.y));
            }
        }
        
        spawnEnemyInWorld(world, tileSetTexture, drawScale, sf::Vector2f(250.f, 480.f));
        spawnEnemyInWorld(world, tileSetTexture, drawScale, sf::Vector2f(350.f, 480.f));

        spawnCoinInWorld(world, tileSetTexture, drawScale, sf::Vector2f(288.f, 288.f));
        spawnCoinInWorld(world, tileSetTexture, drawScale, sf::Vector2f(350.f, 480.f));
   
    
        // Используется для подсчета времени обработки игрового цикла
        sf::Clock clock;
    
        // Основной цикл игры. Происходит пока игра не окончена. Если игрок проиграл, то вся игра перезапускается с полным пересозданием мира
        while (!world.bGameOver && window.isOpen())
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
                HandleWindowsEvent(event, *world.player);
            }

            HandleInput( *world.player);

            UpdateGame(world, clockDeltaSeconds, tileSize);

            DrawGame(window, world, tileSize);
        }
    }

    return 0;
}