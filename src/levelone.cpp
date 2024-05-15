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

    roomOneText = TextureManager::loadTexture("level1room1", "assets/levelone/level1room1.png");
    roomOneSprite.setTexture(*roomOneText);
    roomOneSprite.setScale(1.75, 1.75);
    roomOneSprite.setPosition(0, -475);

    crawlerText = TextureManager::loadTexture("crawlertexture", "assets/levelone/crawlerevent.png");
    crawlerSprite.setTextureRect(crawlerRect);
    crawlerSprite.setTexture(*crawlerText);
    crawlerSprite.setScale(0.5f, 0.5f);
    crawlerSprite.setPosition(400, 355);
    crawlerSprite.setColor(sf::Color(0, 0, 0, 0));
    // crawlerSprite.setPosition();

};

void LevelOne::update(Player *player, sf::RenderWindow &window) {
    if (player->playerSprite.getPosition().x >= 1162 && player->playerSprite.getPosition().x <= 1240) {
        player->doorInteract = true;
        doorText.setPosition(player->playerSprite.getPosition().x + 30, player->playerSprite.getPosition().y - 50); 
        // window.draw(doorText);
        

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
            alphavalue += 10;
        }
        fadeClock.restart();
    }

    window.draw(transitionRect);
}


void LevelOne::render(sf::RenderWindow &window) {
    window.draw(roomOneSprite);
    window.draw(crawlerSprite);
    for (int i = 0; i < 7; i++) {
        // window.draw(skySprites[i]);
    }
};

void LevelOne::move(float dt) {
    for (int i = 1; i < 7; i++) {
        skySprites[i].move(skyParallaxValues[i] * dt, 0);
    }
};

void LevelOne::playEventOne() {
    crawlerSprite.setColor(sf::Color::White);
    eventOneElapsed = eventOneClock.getElapsedTime();
    if (eventOneElapsed.asSeconds() >= 0.08f) {
        if (crawlerRect.left >= crawlerText->getSize().x - 320) {
            crawlerRect.left = 0;
        } else {
            crawlerRect.left += 320;
        }

        if (crawlerRect.left >= 2240) {
            crawlerSprite.move(crawlerSpeed, 0);
        }

        crawlerSprite.setTextureRect(crawlerRect);
        eventOneClock.restart();
    }
}