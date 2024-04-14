#include <SFML/Graphics.hpp>
#include <levelone.hpp>
#include <iostream>
#include <textureManager.hpp>

LevelOne::LevelOne() {
    for (int i = 0; i < 7; i++) {
        std::string name = "sky" + std::to_string(i);
        std::string path = "assets/levelone/sky" + std::to_string(i) + ".png";
        skyTextures[i] = TextureManager::loadTexture(name, path);
        skySprites[i] = sf::Sprite();
        skySprites[i].setTexture(*skyTextures[i]);
        skySprites[i].setScale(2.5, 2.5);
        skySprites[i].setPosition(0, -875);
    }

    font.loadFromFile("C:/Users/johns/Downloads/arial/arial.ttf");
    doorText.setFont(font);
    doorText.setCharacterSize(25); // in pixels, not points
    doorText.setFillColor(sf::Color::White);
    doorText.setString(std::string("Press E to enter"));

    transitionRect.setFillColor(sf::Color::Black);
    transitionRect.setSize(sf::Vector2f(1600, 900));
    transitionRect.setFillColor(sf::Color(0, 0, 0, alphavalue));
};

void LevelOne::update(Player *player, sf::RenderWindow &window) {
    if (player->playerSprite.getPosition().x >= 1162 && player->playerSprite.getPosition().x <= 1240) {
        player->doorInteract = true;
        doorText.setPosition(player->playerSprite.getPosition().x + 30, player->playerSprite.getPosition().y - 50); 
        window.draw(doorText);

        if (playTransition) {
            transition(window);
        }
    } else {
        player->doorInteract = false;
    }
}

void LevelOne::transition(sf::RenderWindow &window) {
    transitionRect.setPosition(600, -100);
    fadeClockElapsed = fadeClock.getElapsedTime();
    if (fadeClockElapsed.asSeconds() >= 0.005) {
        if (alphavalue < 255) {
            transitionRect.setFillColor(sf::Color(0, 0, 0, alphavalue));
            alphavalue+= 5;
        }
        fadeClock.restart();
    }

    window.draw(transitionRect);
}


void LevelOne::render(sf::RenderWindow &window) {
    for (int i = 0; i < 7; i++) {
        window.draw(skySprites[i]);
    }
};

void LevelOne::move(float dt) {
    for (int i = 1; i < 7; i++) {
        skySprites[i].move(skyParallaxValues[i] * dt, 0);
    }
};