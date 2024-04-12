#include <spriteManager.hpp>
#include <SFML/Graphics.hpp>
#include <spriteManager.hpp>
#include <Enemy.hpp>
#include <iostream>

using namespace std;

void SpriteManager::addEnemy(Enemy *enemy) {
    enemies.push_back(enemy);
}

bool SpriteManager::isMarkedForRemoval(Enemy *enemy) {
    return enemy->markedForRemoval;
}

void SpriteManager::removeEnemies() {
    for (auto it = enemies.begin(); it != enemies.end(); /* no increment here */) {
        if ((*it)->markedForRemoval) {
            delete *it;
            it = enemies.erase(it);  // After erasing, it is automatically pointing to the next element
        } else {
            ++it;  // Move to the next element
        }
    }
}

void SpriteManager::updateEnemies(sf::Sprite &player, float dt, bool isAttacking, sf::Texture *enemyT, sf::Texture *deathT, sf::Texture *hitT, sf::Texture *attackT, int playerDirection, int comboNumber) {
    if (enemies.size() < 1) {
            Enemy *enemy = new Enemy(enemyT, deathT, hitT, attackT);
            addEnemy(enemy);
    }

    for (const auto& enemy : enemies) {
        if (enemy->markedForRemoval)
            removeEnemies();
        else
            enemy->movement(player, dt, isAttacking, playerDirection, comboNumber);
    }
}

void SpriteManager::drawEnemies(sf::RenderWindow& renderWindow, sf::Sprite &player) {
    // enemies.at(0)->move(player, dt);
    for (const auto& enemy : enemies) {
        renderWindow.draw(enemy->enemySprite);
        
    }
}