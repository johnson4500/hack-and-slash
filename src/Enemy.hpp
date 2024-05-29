#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <random>
#include <spriteManager.hpp>
#include <textureManager.hpp>
#include <Entity.hpp>

using namespace std;

struct Enemy : public Entity {
    public:
        void update(sf::RenderWindow &window, sf::Event &event) override;
        void move(float dt, int direction) override;
        void changeAnimation(sf::Texture *newTexture, sf::IntRect &newTextureRect) override;
        void handleGravity(float dt, int groundHeight) override;
        sf::Clock c1;
        sf::Time elapsed;
        sf::Clock c2;
        sf::Time elapsed2;
        sf::Clock c3;
        sf::Time elapsed3;
        sf::Clock c4;
        sf::Time elapsed4;
        sf::Clock c5;
        sf::Time elapsed5;

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
        bool isAttacking;
        bool markedForRemoval;

        Enemy(sf::Texture *texture1, sf::Texture *texture2, sf::Texture *texture3, sf::Texture *texture4);

        Enemy(sf::Texture enemyTexture, sf::Sprite enemySprite, sf::Vector2f enemyPosition, bool deathAnimation, bool isDead);

        int getRandomNumber(int min, int max);

        void movementAnimate(sf::Time &elapsed, sf::Clock &clock, sf::IntRect &sourceRect, sf::Sprite &enemySprite, sf::Texture texture);

        void returnToDefaultSprite(sf::Time &elapsed, sf::Clock &clock, sf::IntRect &sourceRect, sf::Sprite &enemySprite);

        void deathAnimate(sf::Time &elapsed, sf::Clock &clock, sf::IntRect &deathSourceRect, sf::Sprite &enemySprite);

        void hitAnimate(sf::Time&elapsed, sf::Clock &clock, sf::Sprite &enemySprite, int &isHit, int &comboNumber);

        void attack(sf::Time &elapsed, sf::Clock &clock, sf::Sprite &enemySprite, sf::IntRect &attackSourceRect);

        void spriteIsDead();

        void movement(sf::Sprite &player, float dt, bool playerAttack, int playerDirection, int comboNumber);
};





