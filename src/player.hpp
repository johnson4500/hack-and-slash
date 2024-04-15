#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <animation.hpp>

struct Player {
    Animation *animator;
    sf::Sprite playerSprite;
    sf::Texture *playerTexture;
    sf::IntRect sourceSprite = sf::IntRect(0, 0, 320, 320);
    sf::Texture idle;
    sf::Texture walking;
    
    sf::CircleShape spotLight[3];
    bool spotLightOn = false;
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

    void update(sf::RenderWindow &window, sf::Event &event);

    void playerMove(float dt);

    void changeAnimation(sf::Texture *newTexture, sf::IntRect &newTextureRect);

    void loadSpotLight();

};

#endif