#pragma once

#include "World.h"

void HandleInput(Player& player);

void HandleWindowsEvent(const sf::Event& event, Player& player);

void UpdateGame(World& world, float clockDeltaSeconds, const sf::Vector2f& tileSize);

void DrawGame(sf::RenderWindow& window, World& world, const sf::Vector2f& tileSize);