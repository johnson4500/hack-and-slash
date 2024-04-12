#include <textureManager.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <map>
#include <memory>

TextureManager::TextureManager(){};
map<string, sf::Texture*> TextureManager::textureMap;

sf::Texture *TextureManager::loadTexture(string name, string path) {
    sf::Texture *texture = new sf::Texture();
    
    if(texture->loadFromFile(path)) {
        textureMap[name] = texture;
        std::cout << "Texture loaded!";
        return textureMap[name];
        
    } else {
        std::cout << "Texture deleted!";
        delete texture;
        return NULL;
    }
};