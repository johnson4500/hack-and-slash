#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <list>
#include <cmath>
#include <Enemy.hpp>
#include <spriteManager.hpp>
#include <player.hpp>
#include <animation.hpp>

// flag to render entirety of attack animation
bool isAttacking = false;
bool hitBool = false;
bool playerShoot = false;
int gameState = 1;
bool moveCameraFlag = false;

// Player direction boolean flag
bool playerIsRight = true;

bool dodging = false;
int playerSpeed = 100;
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

void gunAnimate(sf::Time &gunClockElapsed, sf::Clock &gunClock, sf::IntRect &gunRect, sf::Sprite &armSprite, sf::View &Camera) {
    gunClockElapsed = gunClock.getElapsedTime();
    if (gunClockElapsed.asSeconds() >= 0.04f) {
        if (gunRect.left >= 630) {
            gunRect.left = 0;
            playerShoot = false;
            Camera.move(-2, -6);
        } else {
            gunRect.left += 320;
            Camera.move(1, 3);
        }
        
        armSprite.setTextureRect(gunRect);
        gunClock.restart();  
    }
}


void moveCamera(sf::Time &cameraElapsed, sf::Clock &cameraClock, sf::View &Camera, bool &moveCameraFlag, sf::Sprite skySprite) {
    cameraElapsed = cameraClock.getElapsedTime();
    if (cameraElapsed.asSeconds() >= 0.005f) {
        if (moveCameraFlag) {
            Camera.move(10, 0);
            skySprite.move(10, 0);

            if ((static_cast<int>(Camera.getCenter().x) - 640) % 960 == 0) {
                moveCameraFlag = false;
            }
        }
        cameraClock.restart();
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
    window.setKeyRepeatEnabled(false);
    // window.setFramerateLimit(144);
    sf::View Camera;
    // float CameraX = 640;
    Camera.setSize(1280, 720);
    Camera.setCenter(640, 320);

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

    sf::Clock cameraClock;
    sf::Time cameraElapsed = cameraClock.getElapsedTime();

    sf::Clock gunClock;
    sf::Time gunClockElapse = gunClock.getElapsedTime();

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

    // Sky texture
    sf::Texture skyTexture;
    sf::Sprite skySprite;
    float skyPos = -100;
    skyTexture.setRepeated(true);
    skyTexture.loadFromFile("C:/Users/johns/Downloads/gamesky.jpg");
    skySprite.setTextureRect(sf::IntRect(0, 0, 120000, 2000));
    skySprite.setTexture(skyTexture);
    skySprite.setPosition(skyPos, -100);
    skySprite.setScale(0.5, 0.7);

    // Enemy sprite
    sf::Sprite enemySprite;
    sf::Texture spriteTexture;
    spriteTexture.loadFromFile("C:/Users/johns/Downloads/caefy.png");
    enemySprite.setScale(0.2, 0.2);
    enemySprite.setTexture(spriteTexture);
    enemySprite.setPosition(800, 400);

    // Player sprite
    sf::Texture playerTextureLeft;
    playerTextureLeft.loadFromFile("C:/Users/johns/Downloads/playerpiskeleftnew.png");
    sf::IntRect sourceSprite(0, 0, 320, 320);
    sf::Sprite player(playerTextureLeft, sourceSprite);
    player.setPosition(200, 200);
    player.setOrigin(160, 160);


    sf::Texture playerTextureMain;
    playerTextureMain.loadFromFile("assets/playeridle.png");
    sf::IntRect playerSourceSprite(0, 0, 320, 320);
    Player* johnson = new Player(playerTextureMain, playerSourceSprite, sf::Vector2f(200, 200));

    sf::Texture playerRun;
    playerRun.loadFromFile("assets/playerrun.png");
    sf::IntRect runRect(0, 0, 320, 320);
    // Animation animator = Animation(playerTextureMain, playerSourceSprite);



    // Player direction marker
    sf::RectangleShape playerArm(sf::Vector2f(120, 10));

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
    sf::Texture *attackT = TextureManager::loadTexture("enemy-attack", "C:/Users/johns/Downloads/attackpiskel.png");

    Enemy* enemy = new Enemy(enemyT, deathT, hitTexture, attackT);
    // Enemy* enemy2 = new Enemy(enemyT, deathT, hitTexture, attackT);
    // enemy2->enemySprite.setPosition(800, 400);

    SpriteManager spriteManager;
    spriteManager.addEnemy(enemy);
    // spriteManager.addEnemy(enemy2);

    // Floor
    sf::Sprite floor;
    sf::Texture grassTexture;
    grassTexture.loadFromFile("C:/Users/johns/Downloads/grass.jpg");
    grassTexture.setSmooth(true);
    grassTexture.setRepeated(true);
    floor.setTextureRect(sf::IntRect(0, 0, 5120, 555));
    floor.setPosition(0, 555);
    // floor.setScale(1, 0.5);
    floor.setTexture(grassTexture);

    // sf::Sprite floor2;
    // floor2.setPosition(1280, 555);
    // floor2.setScale(1, 1);
    // floor2.setTexture(grassTexture);

    sf::RectangleShape button(sf::Vector2f (400, 400));
    button.setFillColor(sf::Color::White);
    button.setPosition(500, 100);


    // Temp bullet 
    sf::RectangleShape bullet(sf::Vector2f (10, 10));
    bullet.setPosition(400, 500);

    // Arm gun texture
    sf::Texture armTexture;
    sf::IntRect gunRect(0, 0, 250, 53);
    
    armTexture.loadFromFile("C:/Users/johns/Downloads/armgunpisk1.png");
    sf::Sprite armSprite(armTexture, gunRect);
    // armSprite.setScale(-1.0f, 1.0f);

    // Temp parallax test
    sf::Texture skyTexture0;
    sf::Sprite skySprite0;

    sf::Texture skyTexture1;
    sf::Sprite skySprite1;

    sf::Texture skyTexture2;
    sf::Sprite skySprite2;

    sf::Texture skyTexture3;
    sf::Sprite skySprite3;

    sf::Texture skyTexture4;
    sf::Sprite skySprite4;

    sf::Texture skyTexture5;
    sf::Sprite skySprite5;

    sf::Texture skyTexture6;
    sf::Sprite skySprite6;

   
    skyTexture0.loadFromFile("C:/Users/johns/Downloads/pixilart-layers/pixil-layer-6.png");
    skySprite0.setTexture(skyTexture0);

    skyTexture1.loadFromFile("C:/Users/johns/Downloads/pixilart-layers/pixil-layer-5.png");
    skySprite1.setTexture(skyTexture1);

    skyTexture2.loadFromFile("C:/Users/johns/Downloads/pixilart-layers/pixil-layer-4.png");
    skySprite2.setTexture(skyTexture2);

    skyTexture3.loadFromFile("C:/Users/johns/Downloads/pixilart-layers/pixil-layer-3.png");
    skySprite3.setTexture(skyTexture3);

    skyTexture4.loadFromFile("C:/Users/johns/Downloads/pixilart-layers/pixil-layer-2.png");
    skySprite4.setTexture(skyTexture4);

    skyTexture5.loadFromFile("C:/Users/johns/Downloads/pixilart-layers/pixil-layer-1.png");
    skySprite5.setTexture(skyTexture5);

    skyTexture6.loadFromFile("C:/Users/johns/Downloads/pixilart-layers/pixil-layer-0.png");
    skySprite6.setTexture(skyTexture6);

    skySprite0.setScale(2.25, 2.25);
    skySprite0.setPosition(0, -750);

    skySprite1.setScale(2.25, 2.25);
    skySprite1.setPosition(0, -750);

    skySprite2.setScale(2.25, 2.25);
    skySprite2.setPosition(0, -750);

    skySprite3.setScale(2.25, 2.25);
    skySprite3.setPosition(0, -750);

    skySprite4.setScale(2.25, 2.25);
    skySprite4.setPosition(0, -750);

    skySprite5.setScale(2.25, 2.25);
    skySprite5.setPosition(0, -750);

    skySprite6.setScale(2.25, 2.25);
    skySprite6.setPosition(0, -750);
    

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
            hitBool = false;
            sf::Event event;
            float dt  = clock.restart().asSeconds();
            float fps = 1.f / dt;

            // Calculate angle between mouse position and player gun
            sf::Vector2i position = sf::Mouse::getPosition(window);
            float opp = position.y - armSprite.getPosition().y - 70;
            float adj = (position.x + (armSprite.getPosition().x - 400)) - armSprite.getPosition().x;
            float hyp = sqrt(pow(adj, 2) + pow(opp, 2));
            float angle = asin(opp / hyp);
            armSprite.setRotation(angle* (180 / M_PI));
            if (position.x < 400) {
                playerDirection = -1; 
                player.setScale(1.0f, 1.0f);
            } else {
                playerDirection = 1;
                player.setScale(-1.0f, 1.0f);
            }
        
            text.setString(std::to_string(fps));

            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    playerShoot = true;
                    bullet.setFillColor((sf::Color::Black));
                    bullet.setPosition(playerArm.getPosition().x, playerArm.getPosition().y - 32);
                }

                // Player jump
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W && player.getPosition().y == groundHeight) {
                    velocity = -jumpSpeed;
                }

                if (isAttacking == false && dodgeClock.getElapsedTime().asSeconds() >= 0.3f && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E) {
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

        
            // Handle animation below
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
                Camera.move(-playerSpeed * dt, 0);
                // skySprite.move(20 * dt, 0);
                skySprite0.move(80 * dt, 0);
                skySprite1.move(50  * dt, 0);
                skySprite2.move(25 * dt, 0);
                skySprite3.move(7.5 * dt, 0);
                skySprite4.move(3.8 * dt, 0);
                skySprite5.move(1.5 * dt, 0);
                
                floor.move(200 * dt, 0);
                playerDirection = -1;
                player.move(-playerSpeed * dt, 0);
                playerIsRight = false;
                player.setScale(1.0f, 1.0f);
                if (!isAttacking && !dodging) {
                    animate(elapsed, c2, sourceSprite, player, playerTextureLeft);
                }
            } else if (sf::Keyboard:: isKeyPressed(sf::Keyboard::D)) {
                Camera.move(playerSpeed * dt, 0);
                // skySprite.move(-20 * dt, 0);
                skySprite0.move(-80 * dt, 0);
                skySprite1.move(-50  * dt, 0);
                skySprite2.move(-25 * dt, 0);
                skySprite3.move(-7.5 * dt, 0);
                skySprite4.move(-3.8 * dt, 0);
                skySprite5.move(-1.5 * dt, 0);
                floor.move(-200 * dt, 0);
                playerDirection = 1;
                player.move(playerSpeed * dt, 0);
                playerIsRight = true;
                player.setScale(-1.0f, 1.0f);
                if (!isAttacking && !dodging) {
                    animate(elapsed, c2, sourceSprite, player, playerTextureLeft);
                }

                johnson->changeAnimation(playerRun, runRect);
                johnson->playerMove(dt);
            } else {
                if (!isAttacking && !dodging && (sourceSprite.left / 320) % 4 != 3) {
                    playerIsRight ? player.setScale(-1.0f, 1.0f) : player.setScale(1.0f, 1.0f);
                    returnToDefaultSprite(elapsed2, c3, sourceSprite, player);
                }

                johnson->changeAnimation(playerTextureMain, sourceSprite);
            }

            johnson->animator->play();

            // Gravity logic for player and enemy
            if (player.getPosition().y < groundHeight || velocity < 0) {
                velocity += gravity * dt; 
            } else {
                player.setPosition(player.getPosition().x, groundHeight);
                velocity = 0;
            }
            
            playerArm.setPosition(player.getPosition());
            armSprite.setPosition(player.getPosition().x - 30, player.getPosition().y - 45);
            
            if (playerShoot) {
                gunAnimate(gunClockElapse, gunClock, gunRect, armSprite, Camera);
            }

            // bullet.move(0.5 * cos(angle), 0.5 * sin(angle));

            if (bullet.getPosition().x < enemy->enemySprite.getPosition().x + 1 && bullet.getPosition().x > enemy->enemySprite.getPosition().x - 1) {
                hitBool = true;
                bullet.setFillColor((sf::Color(255,255,255,0)));
            } else {
                hitBool = false;
            }
            

            // if (static_cast<int>(player.getPosition().x) % (static_cast<int>(Camera.getCenter().x) + 540) == 0) {
            //     moveCameraFlag = true;
            // }

            // moveCamera(cameraElapsed, cameraClock, Camera, moveCameraFlag, skySprite);

            spriteManager.updateEnemies(player, dt, hitBool, enemyT, deathT, hitTexture, attackT, playerDirection, comboNumber);
            player.move(0, velocity * dt);
            // enemyShape.move(0, enemyVelocity * dt);
            // enemyShape.setFillColor(sf::Color::Green);
            // enemy2.movement(player, dt);
            window.clear(sf::Color{ 55, 55, 55, 255 });
            window.setView(Camera);
            // window.draw(skySprite);
            // window.draw(floor);
            spriteManager.drawEnemies(window, player);
            // window.draw(playerArm);
            window.draw(skySprite6);
            window.draw(skySprite5);
            window.draw(skySprite4);
            window.draw(skySprite3);
            window.draw(skySprite2);
            window.draw(skySprite1);
            window.draw(skySprite0);
            window.draw(johnson->player);
            window.draw(player);
            
            // window.draw(bullet);
            // window.draw(armSprite);
            // window.draw(text);
            window.display();    
        }
    }

    return 0;
}