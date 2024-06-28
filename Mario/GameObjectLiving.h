#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "GameObject.h"

class GameObjectLiving : public GameObject
{
public:
    void draw(sf::RenderWindow& window) override;
    
public:
    // Спрайт это часть текстуры с указанием координат в текстуре
    // Спрайт не принимает участие в расчете игровой логики. Он нужен только для отрисовки
    sf::Sprite sprite;

    // Мёртв ли объект
    bool bDead = false;
};
