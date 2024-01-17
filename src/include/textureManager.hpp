#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <map>
#include <memory>

using namespace std;


/* Since sprites only hold a pointer to a texture, the texture becomes invalid as it is
destroyed once the constructor finishes. This is why we need a resource manager that is
always in scope of the Enemy struct.*/
class TextureManager {
    static map<string, sf::Texture*> textureMap;
    public:
        static sf::Texture* loadTexture(string name, string path);

    TextureManager();
};

