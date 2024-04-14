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

int gameState = 1;

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
    window.setKeyRepeatEnabled(false);
    // window.setFramerateLimit(144);
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

    // Enemy sprite
    sf::Sprite enemySprite;
    sf::Texture spriteTexture;
    spriteTexture.loadFromFile("C:/Users/johns/Downloads/caefy.png");
    enemySprite.setScale(0.2, 0.2);
    enemySprite.setTexture(spriteTexture);
    enemySprite.setPosition(800, 400);

    // NEW CLASS INSTANTIATIONS
    sf::IntRect playerSourceSprite(0, 0, 320, 320);
    sf::IntRect runRect(0, 0, 320, 320);
    Player* johnson = new Player(sf::Vector2f(300, 200));
    LevelOne level = LevelOne();

    // Enemy death animation
    sf::Texture deathTexture;
    deathTexture.loadFromFile("C:/Users/johns/Downloads/deathpiskel.png");
    sf::IntRect deathSpriteSource(0, 0, 320, 320);

    sf::Texture *hitTexture= TextureManager::loadTexture("enemy-hit", "C:/Users/johns/Downloads/hit.png");
    sf::Texture *enemyT = TextureManager::loadTexture("enemy", "C:/Users/johns/Downloads/playerpiskleft.png");
    sf::Texture *deathT = TextureManager::loadTexture("enemy-death", "C:/Users/johns/Downloads/deathpiskel.png");
    sf::Texture *attackT = TextureManager::loadTexture("enemy-attack", "C:/Users/johns/Downloads/attackpiskel.png");

    Enemy* enemy = new Enemy(enemyT, deathT, hitTexture, attackT);
    // Enemy* enemy2 = new Enemy(enemyT, deathT, hitTexture, attackT);
    // enemy2->enemySprite.setPosition(800, 400);

    SpriteManager spriteManager;
    spriteManager.addEnemy(enemy);
    // spriteManager.addEnemy(enemy2);

    sf::RectangleShape button(sf::Vector2f (400, 400));
    button.setFillColor(sf::Color::White);
    button.setPosition(500, 100);

    sf::IntRect floorRect(0, 0, 2000, 720);
    level.skySprites[6].setTextureRect(floorRect);
    level.skyTextures[6]->setRepeated(true);
    

    int groundHeight = 475;
    float velocity = 0;
    float enemyVelocity = 0;
    float gravity = 3500;
    float jumpSpeed = 1050;

    int playerDirection = 1;

    while (window.isOpen())
    {

        if (gameState == 0) {
            // Code for handling menu state goes here
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

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

                }

                // Player jump
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W && johnson->playerSprite.getPosition().y == groundHeight) {
                    velocity = -jumpSpeed;
                }

            }

            if (sf::Keyboard:: isKeyPressed(sf::Keyboard::A)) {
                Camera.move(-johnson->playerSpeed * dt, 0);
                level.move(dt);
                johnson->playerDirection = -1;
                playerSourceSprite.left = 0;
                johnson->changeAnimation(TextureManager::textureMap["playerrun"], runRect);
                johnson->playerMove(dt);
            } else if (sf::Keyboard:: isKeyPressed(sf::Keyboard::D)) {
                Camera.move(johnson->playerSpeed * dt, 0);
                level.move(-dt);
                johnson->playerDirection = 1;
                playerSourceSprite.left = 0;
                johnson->changeAnimation(TextureManager::textureMap["playerrun"], runRect);
                johnson->playerMove(dt);
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && johnson->doorInteract == true) {
                level.playTransition = true;
            } else {
                runRect.left = 0;
                johnson->changeAnimation(TextureManager::textureMap["playeridle"], playerSourceSprite);
            }

            johnson->animator->play();

            if (johnson->playerSprite.getPosition().y < groundHeight || velocity < 0) {
                velocity += gravity * dt; 
            } else {
                johnson->playerSprite.setPosition(johnson->playerSprite.getPosition().x, groundHeight);
                velocity = 0;
            }

            // std::cout << johnson->playerSprite.getPosition().x << std::endl;

            // spriteManager.updateEnemies(player, dt, hitBool, enemyT, deathT, hitTexture, attackT, playerDirection, comboNumber);
            johnson->playerSprite.move(0, velocity * dt);
            // enemyShape.move(0, enemyVelocity * dt);
            // enemyShape.setFillColor(sf::Color::Green);
            // enemy2.movement(player, dt);
            window.clear(sf::Color{ 55, 55, 55, 255 });
            window.setView(Camera);
            // spriteManager.drawEnemies(window, player);
            level.render(window);
            window.draw(johnson->playerSprite);
            level.update(johnson, window);  
            // window.draw(text);
            window.display();    
        }
    }

    return 0;
}