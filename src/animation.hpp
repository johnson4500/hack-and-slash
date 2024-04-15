#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
// #include <player.hpp>

struct Animation {
    float frameDuration;
    sf::Time elapsedTime;
    sf::Clock clock;
    sf::Texture *animationTexture;
    sf::IntRect *textureRect;
    sf::Sprite *sprite;

    Animation(sf::Texture *animationTexture, sf::IntRect *textureRect, sf::Sprite *sprite);

    void setTexture(sf::Texture *animationTexture, sf::IntRect *newTextureRect);

    void play();
};

#endif