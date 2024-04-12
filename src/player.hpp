#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <animation.hpp>

struct Player {
    private:
        
    public:
        Animation *animator;
        sf::Sprite player;
        sf::Texture playerTexture;
        sf::IntRect sourceSprite;
        sf::Texture idle;
        sf::Texture walking;
        float playerSpeed;
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

        Player(sf::Texture &playerTexture, sf::IntRect &sourceSprite, sf::Vector2f playerPosition);

        void playerMove(float dt);

        void animate();

        void changeAnimation(sf::Texture &newTexture, sf::IntRect &newTextureRect);
    
};