#pragma once

#include "StaticObject.h"
#include "SFML/Graphics.hpp"

struct Player
{
    StaticObject staticObj;

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
};