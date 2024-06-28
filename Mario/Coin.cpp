#include "Coin.h"

#include "World.h"

Coin* createCoint(const sf::Texture& tileSetTexture, sf::Vector2f drawScale, sf::Vector2f position)
{
    Coin* coin = new Coin;

    const sf::Vector2i coinTexturesSize(10, 14);

    coin->sprite.setTexture(tileSetTexture);
    coin->sprite.setTextureRect(sf::IntRect(427, 163, coinTexturesSize.x, coinTexturesSize.y));
    coin->sprite.setScale(drawScale);

    coin->rect = sf::FloatRect(position.x, position.y, coinTexturesSize.x * drawScale.x, coinTexturesSize.y * drawScale.y);

    return coin;
}

Coin* spawnCoinInWorld(World& world, const sf::Texture& tileSetTexture, sf::Vector2f drawScale, sf::Vector2f position)
{
    Coin* coin = createCoint(tileSetTexture, drawScale, position);
    coin->world = &world;

    world.coins.push_back(coin);
    world.objects.push_back(coin);

    return coin;
}
