#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <Enemy.hpp>

TextureManager::TextureManager(){};
map<string, sf::Texture*> TextureManager::textureMap;

sf::Texture *TextureManager::loadTexture(string name, string path) {
    sf::Texture *texture = new sf::Texture();
    
    if(texture->loadFromFile(path)) {
        textureMap[name] = texture;
        return textureMap[name];
    } else {
        delete texture;
        return NULL;
    }
};