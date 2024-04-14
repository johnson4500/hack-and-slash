#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <animation.hpp>

struct Player {
    private:
        
    public:
        Animation *animator;
        sf::Sprite playerSprite;
        sf::Texture *playerTexture;
        sf::IntRect sourceSprite = sf::IntRect(0, 0, 320, 320);
        sf::Texture idle;
        sf::Texture walking;
        float playerSpeed;
        bool doorInteract = false;
        int playerDirection;
        bool isAttacking = false;   
        bool hitBool = false;
        bool playerShoot = false;
        bool moveCameraFlag = false;
        bool playerIsRight = true;
        bool dodging = false;
        int comboNumber = 2;
        sf::Texture texture;

        Player();

        Player(sf::Vector2f playerPosition);

        void playerMove(float dt);

        void animate();

        void changeAnimation(sf::Texture *newTexture, sf::IntRect &newTextureRect);
    
};

#endif