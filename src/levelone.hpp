#include <SFML/Graphics.hpp>
#include <player.hpp>
#include <iostream>
#include <string>
#include <format>

class LevelOne {
    public:
        sf::Texture* skyTextures[7];
        sf::Sprite skySprites[7];
        float skyParallaxValues[7] = {1, 1.5, 3.8, 7.5, 25, 50, 80};
        sf::Font font;
        sf::Text doorText;

        sf::Texture* roomOneText;
        sf::Sprite roomOneSprite;

        sf::Texture* crawlerText;
        sf::IntRect crawlerRect = sf::IntRect(0, 0, 320, 320);
        sf::Sprite crawlerSprite;
    
        bool playTransition = false;
        bool playEvent = false;

        sf::Clock fadeClock;
        sf::Time fadeClockElapsed;

        sf::Clock eventOneClock;
        sf::Time eventOneElapsed;

        sf::RectangleShape transitionRect;
        int alphavalue = 0;
        int crawlerSpeed = 10;

        LevelOne();

        void update(Player *player, sf::RenderWindow &window);

        void transition(sf::RenderWindow &window);

        void render(sf::RenderWindow &window);

        void move(float dt);

        void playEventOne();
};