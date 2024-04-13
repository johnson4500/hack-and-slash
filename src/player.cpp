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
    this->playerSpeed = 100;
    animator = new Animation(playerTexture, &sourceSprite, &playerSprite);
};

void Player::playerMove(float dt) {
    playerSprite.move(playerSpeed * dt * playerDirection, 0);
    playerIsRight = false;
    playerSprite.setScale(1.0f * playerDirection, 1.0f);
    // if (!isAttacking && !dodging) {
    //     animate(elapsed, c2, sourceSprite, player, playerTextureLeft);
    // }
    // animator->play();
};

void Player::changeAnimation(sf::Texture *newTexture, sf::IntRect &newTextureRect) {
    this->playerSprite.setTexture(*newTexture);
    animator->setTexture(newTexture, &newTextureRect);
}

void Player::animate() {
    
}