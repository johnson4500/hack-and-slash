#include <player.hpp>
#include <iostream>
#include <animation.hpp>
#include <textureManager.hpp>

Player::Player(sf::Vector2f playerPosition) {
    // loadTexture() returns a pointer
    TextureManager::loadTexture("playeridle", "assets/playeridle.png");
    TextureManager::loadTexture("playerrun", "assets/playerrun.png");
    this->playerTexture = TextureManager::textureMap["playeridle"];
    this->sourceSprite.left = 0;
    this->playerSprite.setPosition(playerPosition);
    this->playerSprite.setOrigin(160, 160);
    this->playerSprite.setScale(1.0f, 1.0f);
    this->playerSpeed = 150;
    animator = new Animation(playerTexture, &sourceSprite, &playerSprite);
    loadSpotLight();
}

void Player::update(sf::RenderWindow &window, sf::Event &event) {
    if (spotLightOn) {
        for (int i = 0; i < 4; i++) {
            window.draw(spotLight[i]);
        }
    }
}

void Player::playerMove(float dt) {
    playerSprite.move(playerSpeed * dt * playerDirection, 0);
    playerIsRight = false;
    playerSprite.setScale(1.0f * playerDirection, 1.0f);

    for (int i = 0; i < 4; i++) {
        spotLight[i].move(playerSpeed * dt * playerDirection, 0);
    }
}

void Player::changeAnimation(sf::Texture *newTexture, sf::IntRect &newTextureRect) {
    this->playerSprite.setTexture(*newTexture);
    animator->setTexture(newTexture, &newTextureRect);
}

void Player::loadSpotLight() {
    spotLight[0] = sf::CircleShape(188);
    spotLight[0].setOutlineColor(sf::Color(0, 0, 0, 175));
    spotLight[0].setOutlineThickness(15);
    

    spotLight[1] = sf::CircleShape(150);
    spotLight[1].setOutlineColor(sf::Color(0, 0, 0, 125));
    spotLight[1].setOutlineThickness(38);

    spotLight[2] = sf::CircleShape(203);
    spotLight[2].setOutlineColor(sf::Color(0, 0, 0, 200));
    spotLight[2].setOutlineThickness(1000);

    spotLight[3] = sf::CircleShape(110);
    spotLight[3].setOutlineColor(sf::Color(0, 0, 0, 50));
    spotLight[3].setOutlineThickness(40);

    for (int i = 0; i < 4; i++) {
        spotLight[i].setFillColor(sf::Color(0, 0, 0, 0));
        spotLight[i].setPosition(295, 370);
        spotLight[i].setOrigin(spotLight[i].getRadius(), spotLight[i].getRadius());
    }
}
