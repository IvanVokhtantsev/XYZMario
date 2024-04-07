#pragma once

#include "Player.h"
#include "Collisions.h"

void HandleInput(Player& player);

void HandleWindowsEvent(const sf::Event& event, Player& player);

void UpdateGame(Player& player, const Level& level, float gravity, float clockDeltaSeconds, const sf::Vector2f& tileSize);

void DrawGame(sf::RenderWindow& window, Level& level, Player& player, const sf::Vector2f& tileSize);