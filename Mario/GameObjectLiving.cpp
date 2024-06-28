#include "GameObjectLiving.h"

#include "World.h"

void GameObjectLiving::draw(sf::RenderWindow& window)
{
    if(!bDead)
    {
        sf::Vector2f drawPosition = rect.getPosition();
        drawPosition -= world->camera.position;
        sprite.setPosition(drawPosition);
        window.draw(sprite);
    }
}
