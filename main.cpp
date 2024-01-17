#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <list>
#include <second.hpp>
#include <spriteManager.hpp>

// flag to render entirety of attack animation
bool isAttacking = false;
bool hitBool = false;

// Player direction boolean flag
bool playerIsRight = true;

bool dodging = false;
int playerSpeed = 400;
int comboNumber = 2;


// Walking animations
void animate(sf::Time &elapsed, sf::Clock &clock, sf::IntRect &sourceSprite, sf::Sprite &player, sf::Texture texture) {
    elapsed = clock.getElapsedTime();
    if (elapsed.asSeconds() >= 0.08f) {
        if (sourceSprite.left == texture.getSize().x - 320)
            sourceSprite.left = 0;
        else
            sourceSprite.left += 320;   
        player.setTextureRect(sourceSprite);
        clock.restart();
    }   
}

// Return player to default sprite frame when they stop moving
void returnToDefaultSprite(sf::Time &elapsed2, sf::Clock &c3, sf::IntRect &sourceSprite, sf::Sprite &player) {
    elapsed2 = c3.getElapsedTime();
    if (elapsed2.asSeconds() >= 0.08f) {
        if (sourceSprite.left > 2240)
            sourceSprite.left = 0;
        else if ((sourceSprite.left / 320) % 4 != 3)
            sourceSprite.left += 320;
        player.setTextureRect(sourceSprite);
        c3.restart();
    } 
}

// Attack animations
void spriteAttack(sf::Time &elapsed3, sf::Clock &c4, sf::IntRect &attackSourceSprite, sf::Sprite &player) {
    elapsed3 = c4.getElapsedTime();
    if (elapsed3.asSeconds() >= 0.04f) {
        attackSourceSprite.left += 320;
        player.setTextureRect(attackSourceSprite);
        c4.restart();
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
    window.setKeyRepeatEnabled(false);
    // window.setFramerateLimit(144);
    // sf::View Camera;
    // Camera.setSize(1280, 720);
    // Camera.setCenter(640, 320);

    // Some temporary clocks while I create a movement class
    sf::Clock clock;
    sf::Clock c2;
    sf::Time elapsed = c2.getElapsedTime();

    sf::Clock c3;
    sf::Time elapsed2 = c3.getElapsedTime();

    sf::Clock c4;
    sf::Time elapsed3 = c4.getElapsedTime();

    sf::Clock c5;
    sf::Time elapsed4 = c5.getElapsedTime();

    sf::Clock comboreset;
    sf::Time elapse5 = comboreset.getElapsedTime();

    sf::Clock finalHit;
    sf::Clock dodgeClock;

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

    // Player sprite
    sf::Texture playerTextureLeft;
    playerTextureLeft.loadFromFile("C:/Users/johns/Downloads/playerpiskleft.png");
    sf::IntRect sourceSprite(0, 0, 320, 320);
    sf::Sprite player(playerTextureLeft, sourceSprite);
    player.setPosition(400, 400);
    player.setOrigin(160, 160);

    // Player attack sprite
    sf::Texture attackTextureLeft;
    attackTextureLeft.loadFromFile("C:/Users/johns/Downloads/attackpiskel.png");
    sf::IntRect attackSpriteSource(0, 0, 320, 320);

    // Second player attack
    sf::Texture secondAttackLeft;
    secondAttackLeft.loadFromFile("C:/Users/johns/Downloads/secondattackleft.png");

    // Third player attack
    sf::Texture thirdAttack;
    thirdAttack.loadFromFile("C:/Users/johns/Downloads/thirdattack.png");

    sf::Texture attackList[3];
    attackList[0] = attackTextureLeft;
    attackList[1] = secondAttackLeft;
    attackList[2] = thirdAttack;

    // Player dodge
    sf::Texture dodge;
    dodge.loadFromFile("C:/Users/johns/Downloads/dodge.png");

    // Enemy death animation
    sf::Texture deathTexture;
    deathTexture.loadFromFile("C:/Users/johns/Downloads/deathpiskel.png");
    sf::IntRect deathSpriteSource(0, 0, 320, 320);

    sf::Texture *hitTexture= TextureManager::loadTexture("enemy-hit", "C:/Users/johns/Downloads/hit.png");
    sf::Texture *enemyT = TextureManager::loadTexture("enemy", "C:/Users/johns/Downloads/playerpiskleft.png");
    sf::Texture *deathT = TextureManager::loadTexture("enemy-death", "C:/Users/johns/Downloads/deathpiskel.png");

    Enemy* enemy = new Enemy(enemyT, deathT, hitTexture);
    Enemy* enemy2 = new Enemy(enemyT, deathT, hitTexture);
    enemy2->enemySprite.setPosition(800, 400);

    SpriteManager spriteManager;
    spriteManager.addEnemy(enemy);
    spriteManager.addEnemy(enemy2);

    // Floor
    sf::RectangleShape floor(sf::Vector2f(1280, 100));
    floor.setPosition(0, 455);

    int groundHeight = 400;
    float velocity = 0;
    float enemyVelocity = 0;
    float gravity = 3500;
    float jumpSpeed = 1050;

    int playerDirection = 1;

    while (window.isOpen())
    {
        hitBool = false;
        sf::Event event;
        float dt  = clock.restart().asSeconds();
        float fps = 1.f / dt;
        
        text.setString(std::to_string(fps));

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Player jump
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W && player.getPosition().y == groundHeight) {
                velocity = -jumpSpeed;
            }

            if  (isAttacking == false && dodgeClock.getElapsedTime().asSeconds() >= 0.3f && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E) {
                attackSpriteSource.left = 0;
                player.setTexture(dodge);
                dodging = true;
                dodgeClock.restart();
            }

            if (c5.getElapsedTime().asSeconds() >= 0.1f && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                if (isAttacking && comboNumber == 2 && finalHit.getElapsedTime().asSeconds() <= 0.3f) {
                } else {
                    isAttacking = true;
                    hitBool = true;
                    comboNumber++;
                    if (comboNumber > 2) 
                        comboNumber = 0;
                    attackSpriteSource.left = 0;
                    player.setTexture(attackList[comboNumber]);
                }
                
                finalHit.restart();
                c5.restart();
                comboreset.restart();
            }
        }

        if (comboreset.getElapsedTime().asSeconds() > 0.4f) {
            comboNumber = 2;
        }

        if (isAttacking || dodging) {
            spriteAttack(elapsed3, c4, attackSpriteSource, player);
            if (dodging && !isAttacking) player.move(playerDirection * 600 * dt, 0);
            // Check if the animation is complete
            if (attackSpriteSource.left >= player.getTexture()->getSize().x - 320 /* calculate the total width of your attack sprite sheet */) {
                // Animation is complete, reset variables
                attackSpriteSource.left = 0;
                player.setTexture(playerTextureLeft);
                player.setTextureRect(sourceSprite);
                isAttacking = false;
                dodging = false;
            }
        }

        if (sf::Keyboard:: isKeyPressed(sf::Keyboard::A)) {
            playerDirection = -1;
            player.move(-playerSpeed * dt, 0);
            playerIsRight = false;
            player.setScale(1.0f, 1.0f);
            if (!isAttacking && !dodging) {
                animate(elapsed, c2, sourceSprite, player, playerTextureLeft);
            }
        } else if (sf::Keyboard:: isKeyPressed(sf::Keyboard::D)) {
            playerDirection = 1;
            player.move(playerSpeed * dt, 0);
            playerIsRight = true;
            player.setScale(-1.0f, 1.0f);
            if (!isAttacking && !dodging) {
                animate(elapsed, c2, sourceSprite, player, playerTextureLeft);
            }
        } else {
            if (!isAttacking && !dodging && (sourceSprite.left / 320) % 4 != 3) {
                playerIsRight ? player.setScale(-1.0f, 1.0f) : player.setScale(1.0f, 1.0f);
                returnToDefaultSprite(elapsed2, c3, sourceSprite, player);
            }
        }

        // Gravity logic for player and enemy
        if (player.getPosition().y < groundHeight || velocity < 0) {
            velocity += gravity * dt; 
        } else {
            player.setPosition(player.getPosition().x, groundHeight);
            velocity = 0;
        }

        spriteManager.updateEnemies(player, dt, hitBool, enemyT, deathT, hitTexture, playerDirection, comboNumber);
        player.move(0, velocity * dt);
        // enemyShape.move(0, enemyVelocity * dt);
        // enemyShape.setFillColor(sf::Color::Green);
        // enemy2.movement(player, dt);
        window.clear(sf::Color{ 55, 55, 55, 255 });
        window.draw(floor);
        spriteManager.drawEnemies(window, player);
        window.draw(player);
        window.draw(text);
        
        window.display();
    }

    return 0;
}