#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <map>
#include <memory>

using namespace std;

struct Enemy;

class SpriteManager {
    public:
        void addEnemy(Enemy *enemy);
        void removeEnemies();
        void updateEnemies(sf::Sprite &player, float dt, bool isAttacking, sf::Texture *enemyT, sf::Texture *deathT, sf::Texture *hitT, int playerDirection, int comboNumber);
        void drawEnemies(sf::RenderWindow &window, sf::Sprite &player);
        bool isMarkedForRemoval(Enemy *enemy);
    private:
        vector<Enemy*> enemies;
};