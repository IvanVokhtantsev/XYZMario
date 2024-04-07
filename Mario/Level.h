#pragma once

#include "TileTypes.h"

#include <SFML/Graphics.hpp>

#include <map>
#include <vector>

// Структура для описания тайла. Она нужна чтобы перевести символ из описания нашей карты в полностью понятный объект
struct Tile
{
    ETileTextureType textureType;
    ETileCollisionType collisionType;
};

// Структура для игровой карты
// Содержит информацию обо всех тайлах
struct Level
{
    std::vector<std::vector<Tile>> tiles;
    std::map<ETileTextureType, sf::Sprite> tileTextureTypeToSprite;
};

// Описатель игровой карты. По сути редактор на минималках
struct LevelDescriptor
{
    // Сама карта которая представлена символами
    std::vector<std::vector<char>> levelSymbols;
    // Текстура тайслета карты
    sf::Texture tileSetTexture;
    // Соответствие типа текстуры тайла и его координат в текстуре
    std::map<ETileTextureType, sf::IntRect> tileTextureTypeToTextureRect;
};

Level CreateLevel(const LevelDescriptor& levelDescriptor, sf::Vector2f tileScale);