﻿#include "GameLogic.h"
#include "Collisions.h"

#include <algorithm>

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
        for(Enemy* enemy : world.enemies)
        {
            if(!enemy->bDead)
            {
                enemy->rect.left += enemy->enemyVelocity.x * clockDeltaSeconds;
                CollisionResult collisionResult = HandleCollision(enemy->rect, enemy->enemyVelocity, world.level, EOrientaion::Horizontal, tileSize);
                if(collisionResult.bIsCollided)
                {
                    enemy->rect.left = collisionResult.newPosition.x;
                    enemy->enemyVelocity.x *= -1;
                }
            }
        }
    }

    // Обработка логики игрока
    {
        // На игрока постоянно оказывает влияние гравитация и тянет его вниз
        // Во время прыжка она будет всегда замедлять прыжок пока игрок не начнет двигаться вниз

        const sf::Vector2f cachedPlayerVelocity = world.player->playerVelocity;
        Player& player = *world.player;
        
        player.playerVelocity.y += world.gravity * clockDeltaSeconds;

        {
            player.rect.left += player.playerVelocity.x * clockDeltaSeconds;
            CollisionResult collisionResult = HandleCollision(player.rect, player.playerVelocity, world.level, EOrientaion::Horizontal, tileSize);
            if(collisionResult.bIsCollided)
            {
                player.rect.left = collisionResult.newPosition.x;
            }
        }
            
        {
            player.rect.top -= player.playerVelocity.y * clockDeltaSeconds;
            CollisionResult collisionResult = HandleCollision(player.rect, player.playerVelocity, world.level, EOrientaion::Vertical, tileSize);
            if(collisionResult.bIsCollided)
            {
                player.rect.top = collisionResult.newPosition.y;
                
                if(world.player->playerVelocity.y < 0)
                {
                    player.bIsPlayerOnGround = true;
                }
                player.playerVelocity.y = 0.f;
            }
        }

        {
            if(world.renderWindow != nullptr)
            {
                world.camera.position.x = player.rect.getPosition().x;
                world.camera.position.x -= world.renderWindow->getSize().x / 2 - player.rect.width / 2.f;

                const float minCameraX = 0.f;
                const float maxCameraX = world.level.tiles[0].size() * tileSize.x - world.renderWindow->getSize().x;
                world.camera.position.x = std::clamp(world.camera.position.x, minCameraX, maxCameraX);
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
        
        for(Enemy* enemy : world.enemies)
        {
            if(!enemy->bDead)
            {
                // Проверяем столкновение игрока с врагом
                if(world.player->rect.intersects(enemy->rect))
                {
                    // Если игрок находится выше врага и скорость игрока направлена вниз, т.е. игрок прыгнул сверху вниз на врага
                    // Враг умираем, а игрок немного подпрыгивает вверх
                    if(!player.bIsPlayerOnGround && player.rect.top < enemy->rect.top && cachedPlayerVelocity.y < 0 )
                    {
                        enemy->bDead = true;
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

        
        for(Coin* coin : world.coins)
        {
            if(!coin->bDead)
            {
                // Проверяем столкновение игрока с монетой
                if(world.player->rect.intersects(coin->rect))
                {
                    coin->bDead = true;
                    player.score += 100;
                }
            }
        }
    }
}

void DrawGame(sf::RenderWindow& window, World& world, const sf::Vector2f& tileSize)
{
    // Очищаем окно от предыдущих изображений
    window.clear();
    
    for(GameObject* object : world.objects)
    {
         object->draw(window);
    }
    // Отрисовка текста с количеством очков
    world.scoreText.setString("SCORE: " + std::to_string(world.player->score));
    window.draw(world.scoreText);
    
    // Выводим отрисованное на экран
    window.display();
}
