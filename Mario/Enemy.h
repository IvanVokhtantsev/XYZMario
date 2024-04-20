﻿#pragma once

#include "SFML/Graphics.hpp"

struct Enemy
{
    // Спрайт врага. Спрайт это часть текстуры с указанием координат в текстуре
    // Спрайт не принимает участие в расчете игровой логики. Он нужен только для отрисовки
    sf::Sprite enemySprite;
    
    // Создание переменной для хранения размера и положения врага
    sf::FloatRect enemyRect;

    // Текущее ускорение врага. Показывает в какую сторону и на сколько быстро двигается игрок
    sf::Vector2f enemyVelocity;
    
    // Скорость врага. Безразмерная величина. Указывает как быстро может двигаться игрок
    float enemySpeed = 220.f;

    // Мёртв ли враг
    bool bDead = false;
};