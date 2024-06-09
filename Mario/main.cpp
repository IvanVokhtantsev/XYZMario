#include "GameLogic.h"

int main()
{
    // Размер тайла внутри текстуры
    const sf::Vector2i textureTileSize(16.f, 16.f);
    
    // Глобальный скейл для всех спрайтов в игре. Т.к. изначально в текстуре они слишком маленькие
    const sf::Vector2f drawScale(3.f, 3.f);

    const sf::Vector2f tileSize(textureTileSize.x * drawScale.x, textureTileSize.y * drawScale.y);
    
    // Создание основного игрового окна. С размером 800*600
    sf::RenderWindow window(sf::VideoMode(800 , 600), "Mario");
    
    // Текстура с тайлсетом
    sf::Texture tileSetTexture;
    // Загрузка текстуры из файла
    tileSetTexture.loadFromFile("Resources/TileSet.png");

    LevelDescriptor levelDescriptor;
    levelDescriptor.levelSymbols =
        {
        /* 0*/{'B', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'B'}, // level[0]. Чтобы получить 3 нужно level[0][1]
        /* 1*/{'B', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'B'},  // level[1]. Чтобы получить 4 нужно level[1][2]
        /* 2*/{'B', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'B'},
        /* 3*/{'B', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'B'},
        /* 4*/{'B', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'B'},
        /* 5*/{'B', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'B'},
        /* 6*/{'B', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'B'},
        /* 7*/{'B', 'S', 'S', 'S', 'B', 'B', 'B', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'B'},
        /* 8*/{'B', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'B'},
        /* 9*/{'B', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'B'},
        /*10*/{'B', 'S', 'S', 'B', 'S', 'S', 'S', 'S', 'B', 'S', 'S', 'S', 'S', 'S', 'S', 'B'},
        /*11*/{'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B'}
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

        world.scoreText.setFont(font);
        world.scoreText.setCharacterSize(18);
        world.scoreText.setPosition(50.f,50.f);
        world.scoreText.setFillColor(sf::Color::White);
        world.scoreText.setStyle(sf::Text::Style::Bold);
    
        world.level = CreateLevel(levelDescriptor, drawScale);

        {
            // Загружаем текстуру в спрайт
            world.player.staticObj.sprite.setTexture(tileSetTexture);
            // Указываем какую часть текстуры будет использовать спрайт
            world.player.staticObj.sprite.setTextureRect(sf::IntRect(117, 507, textureTileSize.x, textureTileSize.y));
            // Задаём скейл спрайту чтобы его увеличить
            world.player.staticObj.sprite.setScale(drawScale);

            world.player.staticObj.sprite.setOrigin(textureTileSize.x / 2.f, textureTileSize.y / 2.f);

            // Создание переменной для хранения размера и положения игрока
            world.player.staticObj.rect = sf::FloatRect(80.f, 450.f, textureTileSize.x * drawScale.x, textureTileSize.y * drawScale.y);

            // Анимация бега
            {
                world.player.walkAnimation.texture = tileSetTexture;
                world.player.walkAnimation.speed = 7.f;
                world.player.walkAnimation.frames.push_back(sf::IntRect(84, 507, textureTileSize.x, textureTileSize.y));
                world.player.walkAnimation.frames.push_back(sf::IntRect(99, 507, textureTileSize.x, textureTileSize.y));
                world.player.walkAnimation.frames.push_back(sf::IntRect(117, 507, textureTileSize.x, textureTileSize.y));
            }

            {
                world.player.idleAnimation.texture = tileSetTexture;
                world.player.idleAnimation.speed = 0.f;
                world.player.idleAnimation.frames.push_back(sf::IntRect(23, 507, textureTileSize.x, textureTileSize.y));
            }

            {
                world.player.jumpUpAnimation.texture = tileSetTexture;
                world.player.jumpUpAnimation.speed = 0.f;
                world.player.jumpUpAnimation.frames.push_back(sf::IntRect(139, 507, textureTileSize.x, textureTileSize.y));
            }
            {
                world.player.jumpDownAnimation.texture = tileSetTexture;
                world.player.jumpDownAnimation.speed = 7.f;
                world.player.jumpDownAnimation.frames.push_back(sf::IntRect(68, 528, textureTileSize.x, textureTileSize.y));
                world.player.jumpDownAnimation.frames.push_back(sf::IntRect(90, 528, textureTileSize.x, textureTileSize.y));
                world.player.jumpDownAnimation.frames.push_back(sf::IntRect(113, 528, textureTileSize.x, textureTileSize.y));
            }
        }
        
        {
            Enemy enemy;
            //...

            enemy.enemySprite.setTexture(tileSetTexture);
            enemy.enemySprite.setTextureRect(sf::IntRect(187, 894, textureTileSize.x, textureTileSize.y));
            enemy.enemySprite.setScale(drawScale);

            enemy.enemyRect= sf::FloatRect(350.f, 480.f, textureTileSize.x * drawScale.x, textureTileSize.y * drawScale.y);

            enemy.enemySpeed = 150.f;
            enemy.enemyVelocity.x = -enemy.enemySpeed;

            world.enemies.push_back(enemy);
        }
        {
            Enemy enemy;
            //...

            enemy.enemySprite.setTexture(tileSetTexture);
            enemy.enemySprite.setTextureRect(sf::IntRect(187, 894, textureTileSize.x, textureTileSize.y));
            enemy.enemySprite.setScale(drawScale);

            enemy.enemyRect= sf::FloatRect(250.f, 480.f, textureTileSize.x * drawScale.x, textureTileSize.y * drawScale.y);

            enemy.enemySpeed = 150.f;
            enemy.enemyVelocity.x = -enemy.enemySpeed;

            world.enemies.push_back(enemy);
        }

        {
            Coin coin;

            const sf::Vector2i coinTexturesSize(10, 14);

            coin.coinSprite.setTexture(tileSetTexture);
            coin.coinSprite.setTextureRect(sf::IntRect(427, 163, coinTexturesSize.x, coinTexturesSize.y));
            coin.coinSprite.setScale(drawScale);

            coin.coinRect = sf::FloatRect(288.f, 288.f, coinTexturesSize.x * drawScale.x, coinTexturesSize.y * drawScale.y);

            world.coins.push_back(coin);
        }

        {
            Coin coin;

            const sf::Vector2i coinTexturesSize(10, 14);

            coin.coinSprite.setTexture(tileSetTexture);
            coin.coinSprite.setTextureRect(sf::IntRect(427, 163, coinTexturesSize.x, coinTexturesSize.y));
            coin.coinSprite.setScale(drawScale);

            coin.coinRect = sf::FloatRect(350.f, 480.f, coinTexturesSize.x * drawScale.x, coinTexturesSize.y * drawScale.y);

            world.coins.push_back(coin);
        }
    
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
                HandleWindowsEvent(event,  world.player);
            }

            HandleInput( world.player);

            UpdateGame(world, clockDeltaSeconds, tileSize);

            DrawGame(window, world, tileSize);
        }
    }

    return 0;
}