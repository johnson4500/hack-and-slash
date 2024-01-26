#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <random>
#include <spriteManager.hpp>
#include <textureManager.hpp>

using namespace std;

struct Enemy {
    sf::Clock c1;
    sf::Time elapsed;
    sf::Clock c2;
    sf::Time elapsed2;
    sf::Clock c3;
    sf::Time elapsed3;
    sf::Clock c4;
    sf::Time elapsed4;

    sf::Texture *enemyTexture;
    sf::IntRect sourceRect;

    sf::Texture *deathTexture;
    sf::IntRect deathSourceRect;

    sf::Texture *attackTexture;
    sf::IntRect attackSourceRect;

    sf::Texture *hitTexture;
    sf::IntRect helloo;
    sf::Sprite enemySprite;
    int direction;
    int health;
    int isHit;
    bool inRange;
    bool deathAnimation;
    bool isDead;
    
    bool markedForRemoval;

    Enemy(sf::Texture *texture1, sf::Texture *texture2, sf::Texture *texture3, sf::Texture *texture4) {
        this->enemyTexture = texture1;
        this->sourceRect = sf::IntRect(0, 0, 320, 320);
        this->deathTexture = texture2;
        this->hitTexture = texture3;
        this->deathSourceRect = sf::IntRect(0, 0, 320, 320);
        this->attackTexture = texture4;
        this->attackSourceRect = sf::IntRect(0, 0, 320, 320);
        this->helloo = sf::IntRect(0, 0, 320, 320);
        this->enemySprite = sf::Sprite(*enemyTexture, sourceRect);
        this->enemySprite.setOrigin(160, 160);
        this->enemySprite.setPosition(sf::Vector2f(getRandomNumber(0, 1000), 400));
        this->deathAnimation = false;
        this->isDead = false;
        this->elapsed = c1.getElapsedTime();
        this->elapsed2 = c2.getElapsedTime();
        this->elapsed3 = c3.getElapsedTime();
        this->elapsed4 = c4.getElapsedTime();
        this->inRange = false;
        this->markedForRemoval = false;
        this-> health = 100;
        this-> isHit = 100;
    };

    Enemy(sf::Texture enemyTexture, sf::Sprite enemySprite, sf::Vector2f enemyPosition, bool deathAnimation, bool isDead) {
        std::cout << "enemy created!";
    };

    int getRandomNumber(int min, int max) {
        std::random_device rd;  // Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<> dis(min, max);

        return dis(gen);
    }

    void movementAnimate(sf::Time &elapsed, sf::Clock &clock, sf::IntRect &sourceRect, sf::Sprite &enemySprite, sf::Texture texture) {
        // cout << "hllo";
        elapsed = clock.getElapsedTime();
        if (elapsed.asSeconds() >= 0.08f) {
            if (sourceRect.left == texture.getSize().x - 320)
                sourceRect.left = 0;
            else
                sourceRect.left += 320;   
            enemySprite.setTextureRect(sourceRect);
            clock.restart();
        }   
    }

    void returnToDefaultSprite(sf::Time &elapsed, sf::Clock &clock, sf::IntRect &sourceRect, sf::Sprite &enemySprite) {
        elapsed = clock.getElapsedTime();
        if (elapsed.asSeconds() >= 0.08f) {
            if (sourceRect.left > 2240)
                sourceRect.left = 0;
            else if ((sourceRect.left / 320) % 4 != 3)
                sourceRect.left += 320;
            enemySprite.setTextureRect(sourceRect);
            clock.restart();
        } 
    }

    void deathAnimate(sf::Time &elapsed, sf::Clock &clock, sf::IntRect &deathSourceRect, sf::Sprite &enemySprite) {
        elapsed = clock.getElapsedTime();
        if (elapsed.asSeconds() >= 0.04f) {
            deathSourceRect.left += 320;
            enemySprite.setTextureRect(deathSourceRect);
            clock.restart();
        }
    };

    void hitAnimate(sf::Time&elapsed, sf::Clock &clock, sf::Sprite &enemySprite, int &isHit, int &comboNumber) {
        elapsed = clock.getElapsedTime();
        if (elapsed.asSeconds() >= 0.08f) {
            // std::cout << isHit;
            if (isHit < 2) {
                    enemySprite.setColor(sf::Color::Black);
            } else {
                enemySprite.setColor(sf::Color::White);
                enemySprite.setTexture(*enemyTexture);
                enemySprite.setTextureRect(sourceRect);
            }
            isHit+=1;
            clock.restart();
        }
    }

    void attack(sf::Time &elapsed, sf::Clock &clock, sf::Sprite &enemySprite, sf::IntRect &attackSourceRect) {
        elapsed = clock.getElapsedTime();
        if (elapsed.asSeconds() >= 0.03f) {
            if (attackSourceRect.left >= 3520) {
                attackSourceRect.left = 0;
                enemySprite.setTexture(*enemyTexture);
            } else {
                enemySprite.setTextureRect(attackSourceRect);
                attackSourceRect.left += 320;
            }

            clock.restart();
        }
    }

    void spriteIsDead() {
        std::cout << "sprite is dead";
    };

    void movement(sf::Sprite &player, float dt, bool playerAttack, int playerDirection, int comboNumber) {
        // std::cout << enemySprite.getPosition().x << "\n";
        if (!isDead && isHit >= 3) {
            if (enemySprite.getPosition().x > player.getPosition().x + 150) {
                direction = -1;
                inRange = false;
                enemySprite.setScale(1.0f, 1.0f);
                enemySprite.move(direction * 200 * dt, 0);
                enemySprite.setTexture(*enemyTexture);
                movementAnimate(elapsed, c1, sourceRect, enemySprite, *enemyTexture);
            } else if (enemySprite.getPosition().x < player.getPosition().x - 150) {
                direction = 1;
                inRange = false;
                enemySprite.setScale(-1.0f, 1.0f);
                enemySprite.move(direction * 200 * dt, 0);
                enemySprite.setTexture(*enemyTexture);
                movementAnimate(elapsed, c1, sourceRect, enemySprite, *enemyTexture);
            } else if ((sourceRect.left / 320) % 4 != 3) {
                inRange = true;
                returnToDefaultSprite(elapsed2, c2, sourceRect, enemySprite);
            }

            if (enemySprite.getPosition().x < player.getPosition().x + 150 && enemySprite.getPosition().x >= player.getPosition().x) {
                direction = 1;
                inRange = true;
                enemySprite.setTexture(*attackTexture);
                attack(elapsed, c4, enemySprite, attackSourceRect);
            } else if (enemySprite.getPosition().x > player.getPosition().x - 150 && enemySprite.getPosition().x <= player.getPosition().x) {
                direction = -1;
                inRange = true;
                enemySprite.setTexture(*attackTexture);
                attack(elapsed, c4, enemySprite, attackSourceRect);
            }
        }

        if (playerAttack && inRange && playerDirection == direction) {
            health -= 34;
            // enemySprite.setColor(sf::Color::Red);
            if (health <= 0) {
                if (comboNumber == 2) enemySprite.setColor(sf::Color{241, 144, 16, 255});
                deathAnimation = true;
            } else {
                isHit = 0;
                // sourceRect.left = 0;
                enemySprite.setTexture(*hitTexture);
                enemySprite.setTextureRect(helloo);
                hitAnimate(elapsed3, c3, enemySprite, isHit, comboNumber);
            }
        } 

        if (isHit < 3) {
            enemySprite.move(direction * 100 * dt, 0);
            hitAnimate(elapsed3, c3, enemySprite, isHit, comboNumber);
        }
            
        if (deathAnimation) {
            enemySprite.setTexture(*deathTexture);
            deathAnimate(elapsed2, c2, deathSourceRect, enemySprite);
            isDead = true;
            if (deathSourceRect.left >= deathTexture->getSize().x - 320) {
                deathSourceRect.left = 0;
                deathAnimation = false;
                markedForRemoval = true;
            }
        } 
    };
};


