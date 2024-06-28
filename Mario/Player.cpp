#include "Player.h"

#include "World.h"

void Player::draw(sf::RenderWindow& window)
{
    // Берём текущий кадр анимации и устанавливаем его на спрайт игрока
    if(currentAnimation != nullptr)
    {
        sprite.setTextureRect(currentAnimation->GetCurrentFrame());
    }

    // Изменяем scale спрайта игрока в зависимости от направления движения
    // Изменение scale приведет к изменению направления спрайта
    const int scaleXSign = playerAnimationDirection == EPlayerDirection::Left ? -1.f : 1.f;
    const float scaleX = std::abs(sprite.getScale().x) * scaleXSign;
    sprite.setScale(scaleX, sprite.getScale().y);
        
    sf::Vector2f drawPosition ={rect.left + rect.width / 2, rect.top + rect.height / 2};
    drawPosition -= world->camera.position;
        
    sprite.setPosition(drawPosition);
    
    window.draw(sprite);
}
