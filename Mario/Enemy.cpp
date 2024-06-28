#include "Enemy.h"

#include "World.h"

Enemy* createEnemy(const sf::Texture& tileSetTexture, sf::Vector2f drawScale, sf::Vector2f position)
{
    Enemy* enemy = new Enemy;

    const sf::Vector2i textureTileSize(16.f, 16.f);
    
    enemy->sprite.setTexture(tileSetTexture);
    enemy->sprite.setTextureRect(sf::IntRect(187, 894, textureTileSize.x, textureTileSize.y));
    enemy->sprite.setScale(drawScale);

    enemy->rect = sf::FloatRect(position.x, position.y, textureTileSize.x * drawScale.x, textureTileSize.y * drawScale.y);

    enemy->enemySpeed = 150.f;
    enemy->enemyVelocity.x = -enemy->enemySpeed;

    return enemy;
}

Enemy* spawnEnemyInWorld(World& world, const sf::Texture& tileSetTexture, sf::Vector2f drawScale, sf::Vector2f position)
{
    Enemy* enemy = createEnemy(tileSetTexture, drawScale, position);
    enemy->world = &world;
    
    world.enemies.push_back(enemy);
    world.objects.push_back(enemy);

    return enemy;
}
