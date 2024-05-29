#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <SFML/Graphics.hpp>
// Interface for entities such as players, enemies, and NPCs.
class Entity {
    public:
        virtual void update(sf::RenderWindow &window, sf::Event &event) = 0;
        virtual void move(float dt, int direction) = 0;
        virtual void changeAnimation(sf::Texture *newTexture, sf::IntRect &newTextureRect) = 0;
        virtual void handleGravity(float dt, int groundHeight) = 0;
};
#endif