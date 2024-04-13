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
        skySprites[i].setScale(2.25, 2.25);
        skySprites[i].setPosition(0, -750);
    }
};

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