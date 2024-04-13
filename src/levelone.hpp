#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <format>

class LevelOne {
    public:
        sf::Texture* skyTextures[7];
        sf::Sprite skySprites[7];
        float skyParallaxValues[7] = {1, 1.5, 3.8, 7.5, 25, 50, 80};

        LevelOne();

        void render(sf::RenderWindow &window);

        void move(float dt);
};