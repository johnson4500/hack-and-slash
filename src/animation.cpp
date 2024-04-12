#include <animation.hpp>

Animation::Animation(sf::Texture *animationTexture, sf::IntRect *textureRect, sf::Sprite *sprite) {
    this->animationTexture = animationTexture;
    this->textureRect = textureRect;
    this->sprite = sprite;
}

void Animation::setTexture(sf::Texture *newTexture, sf::IntRect *newTextureRect) {
    this->animationTexture = newTexture;  
    this->textureRect = newTextureRect;
    if ((*textureRect).left >= (*animationTexture).getSize().x - 320)
        (*textureRect).left = 0;
};

void Animation::play() {
    std::cout << (*textureRect).left << std::endl;  
    elapsedTime = clock.getElapsedTime();
    if (elapsedTime.asSeconds() >= 0.05f) {
        // if ((*textureRect).left >= (*animationTexture).getSize().x - 320)
        //    (*textureRect).left = 0;
        // else
            (*textureRect).left += 320;   

        (*sprite).setTextureRect((*textureRect));
        clock.restart();
    }   
};