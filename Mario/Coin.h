#pragma once

#include "GameObjectLiving.h"

/*
 * Дочерний класс для монеты
 */
class Coin : public GameObjectLiving
{
public:
};

Coin* createCoint(const sf::Texture& tileSetTexture, sf::Vector2f drawScale, sf::Vector2f position);
Coin* spawnCoinInWorld(World& world, const sf::Texture& tileSetTexture, sf::Vector2f drawScale, sf::Vector2f position);

