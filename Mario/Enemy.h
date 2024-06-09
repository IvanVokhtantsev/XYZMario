#pragma once

#include "GameObject.h"
#include "SFML/Graphics.hpp"

class Enemy : public GameObjectLiving
{
public:
    // Текущее ускорение врага. Показывает в какую сторону и на сколько быстро двигается игрок
    sf::Vector2f enemyVelocity;
    
    // Скорость врага. Безразмерная величина. Указывает как быстро может двигаться игрок
    float enemySpeed = 220.f;
};