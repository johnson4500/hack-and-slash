#include <player.hpp>
#include <iostream>
#include <animation.hpp>

Player::Player(sf::Texture &playerTexture, sf::IntRect &sourceSprite, sf::Vector2f playerPosition) {
    this->sourceSprite = sourceSprite;
    this->playerTexture = playerTexture;
    this->player = sf::Sprite(playerTexture, sourceSprite);
    this->sourceSprite.left = 0;
    this->player.setPosition(playerPosition);
    this->player.setOrigin(160, 160);
    this->player.setScale(1.0f, 1.0f);
    this->playerSpeed = 100;
    animator = new Animation(&playerTexture, &sourceSprite, &player);
};

void Player::playerMove(float dt) {
    playerDirection = 1;
    player.move(playerSpeed * dt, 0);
    playerIsRight = false;
    player.setScale(1.0f, 1.0f);
    // if (!isAttacking && !dodging) {
    //     animate(elapsed, c2, sourceSprite, player, playerTextureLeft);
    // }
    // animator->play();
};

void Player::changeAnimation(sf::Texture &newTexture, sf::IntRect &newTextureRect) {
    this->player.setTexture(newTexture);
    animator->setTexture(&newTexture, &newTextureRect);
}

void Player::animate() {
    
}