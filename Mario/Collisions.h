#pragma once

#include "Level.h"

enum class EOrientaion
{
    Horizontal,
    Vertical
};

/*
 * Структура для хранения результата коллизии
 */
struct CollisionResult
{
    bool bIsCollided = false;
    sf::Vector2f newPosition;
};

/*
 * Функция рассчитывает коллизию объекта с картой
 * Возвращает новое положение объекта после коллизии
 */
CollisionResult HandleCollision(
    const sf::FloatRect& objectRect/*положение и размеры объекта для которого считаем коллизию*/,
    const sf::Vector2f& objectVelocity /*скорость и направление движения объекта*/,
    const Level& level /*карта с тайлами*/,
    EOrientaion orientation /*ориентация коллизии. Горизонтальная или вертикальная*/,
    const sf::Vector2f& tileSize /*размер тайла*/);