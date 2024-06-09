#include "GameLogic.h"
#include "Collisions.h"

void HandleInput(Player& player)
{
    player.playerVelocity.x = 0.f;
    
    // Обработка инпута с кнопок
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        player.playerVelocity.x = -player.playerSpeed;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        player.playerVelocity.x = player.playerSpeed;
    }
}

void HandleWindowsEvent(const sf::Event& event, Player& player)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Space)
        {
            // Если нажали кнопку прыжка и игрок на земле, то запускаем логику прыжка
            if(player.bIsPlayerOnGround)
            {
                player.bIsPlayerOnGround = false;
                player.playerVelocity.y = player.playerJumpSpeed;
            }
        }
    }
}

void UpdateGame(World& world, float clockDeltaSeconds, const sf::Vector2f& tileSize)
{
    // Основной блок обработки игровой логики

    // Обработка логики врагов
    {
        for(Enemy& enemy : world.enemies)
        {
            if(!enemy.bDead)
            {
                enemy.enemyRect.left += enemy.enemyVelocity.x * clockDeltaSeconds;
                CollisionResult collisionResult = HandleCollision(enemy.enemyRect, enemy.enemyVelocity, world.level, EOrientaion::Horizontal, tileSize);
                if(collisionResult.bIsCollided)
                {
                    enemy.enemyRect.left = collisionResult.newPosition.x;
                    enemy.enemyVelocity.x *= -1;
                }
            }
        }
    }

    // Обработка логики игрока
    {
        // На игрока постоянно оказывает влияние гравитация и тянет его вниз
        // Во время прыжка она будет всегда замедлять прыжок пока игрок не начнет двигаться вниз

        const sf::Vector2f cachedPlayerVelocity = world.player.playerVelocity;
        Player& player = world.player;
        
        player.playerVelocity.y += world.gravity * clockDeltaSeconds;

        {
            player.staticObj.rect.left += player.playerVelocity.x * clockDeltaSeconds;
            CollisionResult collisionResult = HandleCollision(player.staticObj.rect, player.playerVelocity, world.level, EOrientaion::Horizontal, tileSize);
            if(collisionResult.bIsCollided)
            {
                player.staticObj.rect.left = collisionResult.newPosition.x;
            }
        }
            
        {
            player.staticObj.rect.top -= player.playerVelocity.y * clockDeltaSeconds;
            CollisionResult collisionResult = HandleCollision(player.staticObj.rect, player.playerVelocity, world.level, EOrientaion::Vertical, tileSize);
            if(collisionResult.bIsCollided)
            {
                player.staticObj.rect.top = collisionResult.newPosition.y;
                
                if(world.player.playerVelocity.y < 0)
                {
                    player.bIsPlayerOnGround = true;
                }
                player.playerVelocity.y = 0.f;
            }
        }

        if(std::abs(player.playerVelocity.x) > 0.0001f)
        {
            player.playerAnimationDirection = player.playerVelocity.x < 0 ? EPlayerDirection::Left : EPlayerDirection::Right;
        }
        
        if(player.bIsPlayerOnGround)
        {
            if(std::abs(player.playerVelocity.x) > 0.0001f)
            {
                player.currentAnimation = &player.walkAnimation;
            }
            else
            {
                player.currentAnimation = &player.idleAnimation;
            }
        }
        else
        {
            if(player.playerVelocity.y < 0)
            {
                player.currentAnimation = &player.jumpDownAnimation;
            }
            else
            {
                player.currentAnimation = &player.jumpUpAnimation;
            }
        }
        

        player.currentAnimation->Update(clockDeltaSeconds);
        
        for(Enemy& enemy : world.enemies)
        {
            if(!enemy.bDead)
            {
                // Проверяем столкновение игрока с врагом
                if(world.player.staticObj.rect.intersects(enemy.enemyRect))
                {
                    // Если игрок находится выше врага и скорость игрока направлена вниз, т.е. игрок прыгнул сверху вниз на врага
                    // Враг умираем, а игрок немного подпрыгивает вверх
                    if(!player.bIsPlayerOnGround && player.staticObj.rect.top < enemy.enemyRect.top && cachedPlayerVelocity.y < 0 )
                    {
                        enemy.bDead = true;
                        player.playerVelocity.y = player.playerKillEnemyJumpSpeed;
                        player.score += 50;
                    }
                    else // Иначе игрок умирает и игра перезапускается
                    {
                        world.bGameOver = true;
                        //выходим с цикла
                        break;
                    }
                }
            }
        }

        
        for(Coin& coin : world.coins)
        {
            if(!coin.bDead)
            {
                // Проверяем столкновение игрока с монетой
                if(world.player.staticObj.rect.intersects(coin.coinRect))
                {
                    coin.bDead = true;
                    player.score += 100;
                }
            }
        }
    }
}

void DrawGame(sf::RenderWindow& window, World& world, const sf::Vector2f& tileSize)
{
    // Блок отрисовки окна
    
    // Очищаем окно от предыдущих изображений
    window.clear();

    // Отрисовываем новые данные в окне,
            
    for(int i = 0; i < world.level.tiles.size(); ++i)
    {
        for(int j = 0; j < world.level.tiles[i].size(); ++j)
        {
            const Tile& tile = world.level.tiles[i][j];

            sf::Sprite& sprite = world.level.tileTextureTypeToSprite[tile.textureType];
            sprite.setPosition(tileSize.x * j, tileSize.y * i);
            window.draw(sprite);
        }
    }

    // Отрисовываем врагов
    for(Enemy& enemy : world.enemies)
    {
        if(!enemy.bDead)
        {
            enemy.enemySprite.setPosition(enemy.enemyRect.left, enemy.enemyRect.top);
            window.draw(enemy.enemySprite);
        }
    }
    
    // Отрисовываем монеты
    for(Coin& coin : world.coins)
    {
        if(!coin.bDead)
        {
            coin.coinSprite.setPosition(coin.coinRect.left, coin.coinRect.top);
            window.draw(coin.coinSprite);
        }
    }

    {
        // Отрисовываем игрока
        
        Player& player = world.player;
      
        // Берём текущий кадр анимации и устанавливаем его на спрайт игрока
        if(player.currentAnimation != nullptr)
        {
            player.staticObj.sprite.setTextureRect(player.currentAnimation->GetCurrentFrame());
        }

        // Изменяем scale спрайта игрока в зависимости от направления движения
        // Изменение scale приведет к изменению направления спрайта
        const int scaleXSign = player.playerAnimationDirection == EPlayerDirection::Left ? -1.f : 1.f;
        const float scaleX = std::abs(player.staticObj.sprite.getScale().x) * scaleXSign;
        player.staticObj.sprite.setScale(scaleX, player.staticObj.sprite.getScale().y);

        const float playerDrawLeftPos = player.staticObj.rect.left + world.player.staticObj.rect.width / 2;
        const float playerDrawTopPos = player.staticObj.rect.top + world.player.staticObj.rect.height / 2;
        player.staticObj.sprite.setPosition(playerDrawLeftPos, playerDrawTopPos);
    }
  
    
    window.draw(world.player.staticObj.sprite);

    // Отрисовка текста с количеством очков
    world.scoreText.setString("SCORE: " + std::to_string(world.player.score));
    window.draw(world.scoreText);
    
    // Выводим отрисованное на экран
    window.display();
}
