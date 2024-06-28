#pragma once

#include "GameObjectLiving.h"

class Enemy : public GameObjectLiving
{
public:
    // Текущее ускорение врага. Показывает в какую сторону и на сколько быстро двигается игрок
    sf::Vector2f enemyVelocity;
    
    // Скорость врага. Безразмерная величина. Указывает как быстро может двигаться игрок
    float enemySpeed = 220.f;
};


Enemy* createEnemy(const sf::Texture& tileSetTexture, sf::Vector2f drawScale, sf::Vector2f position);
Enemy* spawnEnemyInWorld(World& world, const sf::Texture& tileSetTexture, sf::Vector2f drawScale, sf::Vector2f position);
