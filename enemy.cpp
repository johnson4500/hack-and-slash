#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <random>
#include <spriteManager.hpp>
#include <textureManager.hpp> 
#include <Enemy.hpp>  


Enemy::Enemy(sf::Texture *texture1, sf::Texture *texture2, sf::Texture *texture3, sf::Texture *texture4) {
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
    this->enemySprite.setPosition(sf::Vector2f(getRandomNumber(3000, 3500), 500));
    this->deathAnimation = false;
    this->isDead = false;
    this->elapsed = c1.getElapsedTime();
    this->elapsed2 = c2.getElapsedTime();
    this->elapsed3 = c3.getElapsedTime();
    this->elapsed4 = c4.getElapsedTime();
    this->elapsed5 = c5.getElapsedTime();
    this->inRange = false;
    this->markedForRemoval = false;
    this->health = 100;
    this->isHit = 100;
    this->isAttacking = false;
};

Enemy::Enemy(sf::Texture enemyTexture, sf::Sprite enemySprite, sf::Vector2f enemyPosition, bool deathAnimation, bool isDead) {
    std::cout << "enemy created!";
};

int Enemy::getRandomNumber(int min, int max) {
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(min, max);

    return dis(gen);
}

void Enemy::movementAnimate(sf::Time &elapsed, sf::Clock &clock, sf::IntRect &sourceRect, sf::Sprite &enemySprite, sf::Texture texture) {
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

void Enemy::returnToDefaultSprite(sf::Time &elapsed, sf::Clock &clock, sf::IntRect &sourceRect, sf::Sprite &enemySprite) {
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

void Enemy::deathAnimate(sf::Time &elapsed, sf::Clock &clock, sf::IntRect &deathSourceRect, sf::Sprite &enemySprite) {
    elapsed = clock.getElapsedTime();
    if (elapsed.asSeconds() >= 0.04f) {
        deathSourceRect.left += 320;
        enemySprite.setTextureRect(deathSourceRect);
        clock.restart();
    }
};

void Enemy::hitAnimate(sf::Time&elapsed, sf::Clock &clock, sf::Sprite &enemySprite, int &isHit, int &comboNumber) {
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

void Enemy::attack(sf::Time &elapsed, sf::Clock &clock, sf::Sprite &enemySprite, sf::IntRect &attackSourceRect) {
    elapsed = clock.getElapsedTime();
    if (elapsed.asSeconds() >= 0.03f && isAttacking) {
        if (attackSourceRect.left >= enemySprite.getTexture()->getSize().x - 320) {
            attackSourceRect.left = 0;
            isAttacking = false;
        } else {
            enemySprite.setTexture(*attackTexture);
            enemySprite.setTextureRect(attackSourceRect);
            attackSourceRect.left += 320;
        }

        clock.restart();
    }
}

void spriteIsDead() {
    std::cout << "sprite is dead";
};

void Enemy::movement(sf::Sprite &player, float dt, bool playerAttack, int playerDirection, int comboNumber) {
    if (!isDead && isHit >= 3) {
        if (enemySprite.getPosition().x > player.getPosition().x + 150) {
            direction = -1;
            inRange = false;
            enemySprite.setScale(1.0f, 1.0f);
            enemySprite.move(direction * 200 * dt, 0);
            enemySprite.setTexture(*enemyTexture);
            movementAnimate(elapsed, c1, sourceRect, enemySprite, *enemyTexture);
            attackSourceRect.left = 0;
            isAttacking = false;
            c5.restart();
        } else if (enemySprite.getPosition().x < player.getPosition().x - 150) {
            direction = 1;
            inRange = false;
            enemySprite.setScale(-1.0f, 1.0f);
            enemySprite.move(direction * 200 * dt, 0);
            enemySprite.setTexture(*enemyTexture);
            movementAnimate(elapsed, c1, sourceRect, enemySprite, *enemyTexture);
            attackSourceRect.left = 0;
            isAttacking = false;
            c5.restart();
        } else if ((sourceRect.left / 320) % 4 != 3) {
            inRange = true;
            returnToDefaultSprite(elapsed2, c2, sourceRect, enemySprite);
            attackSourceRect.left = 0;
            isAttacking = false;
            c5.restart();
        }

        if (enemySprite.getPosition().x < player.getPosition().x + 600 && enemySprite.getPosition().x >= player.getPosition().x) {
            direction = 1;
            inRange = true;
            if (c5.getElapsedTime().asSeconds() >= 0.55f) {
                isAttacking = true;
                c5.restart();
            }
            if (!playerAttack) {
                attack(elapsed, c4, enemySprite, attackSourceRect);   
            }
        } else if (enemySprite.getPosition().x > player.getPosition().x - 150 && enemySprite.getPosition().x <= player.getPosition().x) {
            direction = -1;
            inRange = true;
            if (c5.getElapsedTime().asSeconds() >= 0.55f) {
                isAttacking = true;
                c5.restart();
            }
            if (!playerAttack) {
                attack(elapsed, c4, enemySprite, attackSourceRect);   
            }
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
