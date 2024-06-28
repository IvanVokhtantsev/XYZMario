#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace sf
{
    class RenderWindow;
}

/* Это forward declaration
 * Она нужна чтобы избежать циклической зависимости между GameObject и World.
 * Циклическая зависимость это когда GameObject выполняет include World и World выполняет include GameObject
 */
class World;

/*
 * В чем отличие структуры от класса?
 * У структуры все члены по умолчанию public, у класса все члены по умолчанию private
 */

/*
 * Базовый класс для всех игровых объектов
 * Все классы которые от него наследуются называются дочерние
 * Все классы которые наследуются буду иметь переменную rect
 */
class GameObject
{
public:
    // Объявляем виртуальную функцию для того чтобы иметь возможность переопределить её в дочерних классах
    virtual void draw(sf::RenderWindow& window)
    {
        
    }
    // В области видимости public все члены класса доступны внешним сущностям
public:
    // Положение и размер объекта в игровом мире
    sf::FloatRect rect;

    World* world = nullptr;

    // В области видимости protected все члены класса доступны самому классу и тем классам которые от него наследуются
protected:
    
    // В области видимости protected все члены класса доступны только самому классу 
private:
};