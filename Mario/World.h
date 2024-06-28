#pragma once

#include "Level.h"
#include "Player.h"
#include "Enemy.h"
#include "Coin.h"
#include "Camera.h"

struct World
{
    Player* player;
    std::vector<Enemy*> enemies;
    std::vector<Coin*> coins;
    std::vector<GameObject*> objects;
    Level level;

    Camera camera;
    
    // Гравитация в игре. То с какой скоростью объекты будут падать вниз
    const float gravity = -700.f;

    bool bGameOver = false;

    sf::Text scoreText;

    sf::RenderWindow* renderWindow = nullptr;
};