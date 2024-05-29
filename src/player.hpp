#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <animation.hpp>
#include <Entity.hpp>

struct Player : public Entity {
    public:
        Player();

        Player(sf::Vector2f playerPosition);

        void update(sf::RenderWindow &window, sf::Event &event) override;

        void move(float dt, int direction) override;

        void changeAnimation(sf::Texture *newTexture, sf::IntRect &newTextureRect) override;

        void handleGravity(float dt, int groundHeight) override;

        // Class getters
        Animation* getAnimator();
        bool getDoorInteract();
        float getPlayerSpeed();
        sf::Vector2f getPlayerPosition();
        sf::Sprite getPlayerSprite();
        float getGravityVelocity();
        float getJumpSpeed();
        bool getSpotLightBool();

        // Class setters
        void setDoorInteract(bool b);
        void setGravityVelocity(float v);
        void setSpotLightBool(bool b);

    private:
        Animation *animator;
        sf::Sprite playerSprite;
        sf::Texture *playerTexture;
        sf::IntRect sourceSprite = sf::IntRect(0, 0, 320, 320);
        sf::Texture idle;
        sf::Texture walking;
    
        sf::CircleShape spotLight[4];
        float gravity = 3500;
        float jumpSpeed = 1050;
        float gravityVelocity = 0;
        bool spotLightOn = true;
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

        void loadSpotLight();
};

#endif