#pragma once

#include "Animation.h"
#include "GameObjectLiving.h"
#include "SFML/Graphics.hpp"

enum class EPlayerDirection
{
    Left,
    Right
};

class Player : public GameObjectLiving
{
public:
    void draw(sf::RenderWindow& window) override;
    
public:
    // Текущее ускорение игрока. Показывает в какую сторону и на сколько быстро двигается игрок
    sf::Vector2f playerVelocity;
    
    // Скорость игрока. Безразмерная величина. Указывает как быстро может двигаться игрок
    float playerSpeed = 220.f;

    // Скорость прыжка игрока аналогично playerSpeed
    float playerJumpSpeed = 450.f;

    // Скорость прыжка игрока когда он убивает врага
    float playerKillEnemyJumpSpeed = 200.f;
    
    // Переменная которая указывает находится ли игрок на земле. Это нужно для опеределия возможности прыжка
    bool bIsPlayerOnGround = false;

    int score = 0;

    // Аниация игрока в состоянии покоя
    Animation idleAnimation;
    // Аниация игрока в состоянии бега
    Animation walkAnimation;
    // Аниация игрока в состоянии прыжка вниз
    Animation jumpDownAnimation;
    // Аниация игрока в состоянии прыжка вверх
    Animation jumpUpAnimation;

    // Направление анимации игрока. Оно нужно чтобы помнить куда игрок был повёрнут в последний раз, даже если сейчас он уже стоит(нужно для определения направления idle анимации)
    EPlayerDirection playerAnimationDirection = EPlayerDirection::Right;

    // Текущая анимация игрока. Определяется в зависимости от состояния игрока(направления его движения)
    Animation* currentAnimation = nullptr;
};
