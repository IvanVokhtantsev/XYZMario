#include "GameLogic.h"

void HandleInput(Player& player)
{
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

void UpdateGame(Player& player, const Level& level, float gravity, float clockDeltaSeconds, const sf::Vector2f& tileSize)
{
    // Основной блок обработки игровой логики
    
    // На игрока постоянно оказывает влияние гравитация и тянет его вниз
    // Во время прыжка она будет всегда замедлять прыжок пока игрок не начнет двигаться вниз
    player.playerVelocity.y += gravity * clockDeltaSeconds;

    {
        player.playerRect.left += player.playerVelocity.x * clockDeltaSeconds;
        CollisionResult collisionResult = HandleCollision(player.playerRect, player.playerVelocity, level, EOrientaion::Horizontal, tileSize);
        if(collisionResult.bIsCollided)
        {
            player.playerRect.left = collisionResult.newPosition.x;
        }
    }
            
    {
        player.playerRect.top -= player.playerVelocity.y * clockDeltaSeconds;
        CollisionResult collisionResult = HandleCollision(player.playerRect, player.playerVelocity, level, EOrientaion::Vertical, tileSize);
        if(collisionResult.bIsCollided)
        {
            player.playerRect.top = collisionResult.newPosition.y;
            if(player.playerVelocity.y < 0)
            {
                player.bIsPlayerOnGround = true;
                player.playerVelocity.y = 0.f;
            }
        }
    }
            
    player.playerVelocity.x = 0.f;
}

void DrawGame(sf::RenderWindow& window, Level& level, Player& player, const sf::Vector2f& tileSize)
{
    // Блок отрисовки окна
    
    // Очищаем окно от предыдущих изображений
    window.clear();

    // Отрисовываем новые данные в окне,
            
    for(int i = 0; i < level.tiles.size(); ++i)
    {
        for(int j = 0; j < level.tiles[i].size(); ++j)
        {
            const Tile& tile = level.tiles[i][j];

            sf::Sprite& sprite = level.tileTextureTypeToSprite[tile.textureType];
            sprite.setPosition(tileSize.x * j, tileSize.y * i);
            window.draw(sprite);
        }
    }
            
    player.playerSprite.setPosition(player.playerRect.left, player.playerRect.top);
    window.draw(player.playerSprite);
    // Выводим отрисованное на экран
    window.display();
}
