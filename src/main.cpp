#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <list>
#include <cmath>
#include <Enemy.hpp>
#include <spriteManager.hpp>
#include <player.hpp>
#include <animation.hpp>
#include <levelone.hpp>
#include <dialogbox.hpp>

int gameState = 1;
int groundHeight = 410;
float gravity = 3500;

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "we're cookin");
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(60);
    sf::View Camera;
    Camera.setSize(1280, 720);
    Camera.setCenter(640, 320);

    // delta time clock
    sf::Clock clock;
    sf::Font font;
    sf::Text text;
    font.loadFromFile("C:/Users/johns/Downloads/arial/arial.ttf");
    text.setFont(font);
    text.setCharacterSize(25); // in pixels, not points
    text.setFillColor(sf::Color::White);
    text.setPosition(10,10);

    // Player object
    Player* johnson = new Player(sf::Vector2f(300, 200));
    sf::IntRect playerSourceSprite(0, 0, 320, 320);
    sf::IntRect runRect(0, 0, 320, 320);
    
    // Level One Object
    LevelOne level = LevelOne();

    sf::RectangleShape button(sf::Vector2f (400, 400));
    button.setFillColor(sf::Color::White);
    button.setPosition(500, 100);

    sf::IntRect floorRect(0, 0, 2000, 720);
    level.skySprites[6].setTextureRect(floorRect);
    level.skyTextures[6]->setRepeated(true);

    sf::Texture spotLightText;
    spotLightText.loadFromFile("assets/spotlight.png");
    sf::Sprite spotLight;
    spotLight.setTexture(spotLightText);
    spotLight.setColor(sf::Color(0, 0, 0, 240));
    spotLight.setPosition(0, -50);
    spotLight.setOrigin(0, 0);

    DialogBox dialogBox = DialogBox();

    // Game loop
    while (window.isOpen())
    {

        if (gameState == 0) {
            // Handling menu state
            sf::Event menuEvent;
            while (window.pollEvent(menuEvent)) {
                if (menuEvent.type == sf::Event::KeyPressed && menuEvent.key.code == sf::Keyboard::Enter) {
                    gameState = 1;  // Switch to game state when Enter key is pressed
                }
            }

            window.draw(button);
            window.display();
        }

        if (gameState == 1) {
            sf::Event event;
            float dt  = clock.restart().asSeconds();
            float fps = 1.f / dt;
        
            text.setString(std::to_string(fps));

            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();

                // Toggle light
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F) {
                    johnson->setSpotLightBool(!(johnson->getSpotLightBool()));
                }

                // Player jump
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W && johnson->getPlayerPosition().y == groundHeight) {
                    johnson->setGravityVelocity(-johnson->getJumpSpeed());
                }

                // Progress through dialog box 
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                    dialogBox.iterate();
                }
            }

            if (sf::Keyboard:: isKeyPressed(sf::Keyboard::A)) {
                if (johnson->getPlayerPosition().x < 755) {
                    Camera.move(-johnson->getPlayerSpeed() * dt, 0);
                    dialogBox.follow(-dt * johnson->getPlayerSpeed());
                }

                spotLight.move(-johnson->getPlayerSpeed() * dt, 0);
                level.move(dt);
                playerSourceSprite.left = 0;
                johnson->changeAnimation(TextureManager::textureMap["playerrun"], runRect);
                johnson->move(dt, -1);
            } else if (sf::Keyboard:: isKeyPressed(sf::Keyboard::D)) {
                if (johnson->getPlayerPosition().x < 755) {
                    Camera.move(johnson->getPlayerSpeed() * dt, 0);
                    dialogBox.follow(dt * johnson->getPlayerSpeed());
                }

                spotLight.move(johnson->getPlayerSpeed() * dt, 0);
                level.move(-dt);
                playerSourceSprite.left = 0;
                johnson->changeAnimation(TextureManager::textureMap["playerrun"], runRect);
                johnson->move(dt, 1);
            } else {
                runRect.left = 0;
                johnson->changeAnimation(TextureManager::textureMap["playeridle"], playerSourceSprite);
            }
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && johnson->getDoorInteract() == true) {
                level.playTransition = true;
            }

            johnson->getAnimator()->play();
            johnson->handleGravity(dt, groundHeight);

            window.clear(sf::Color{ 55, 55, 55, 255 });
            window.setView(Camera);
            level.render(window);
            window.draw(johnson->getPlayerSprite());
            level.update(johnson, window);
            johnson->update(window, event);  

            if (johnson->getPlayerPosition().x >= 1200) {
                if (dialogBox.index == 3) {
                    level.crawlerSpeed = 40;
                }

                level.playEventOne();
                johnson->getPlayerSprite().setScale(-1.0f, 1.0f);
                if (dialogBox.index < 4) {
                    dialogBox.render(window);
                }
            }

            window.display();    
        }
    }

    return 0;
}