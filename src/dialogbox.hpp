#include <SFML/Graphics.hpp>

struct DialogBox {
    sf::Texture* dialogBoxTextures[3];
    sf::Sprite dialogBoxSprite;
    bool open = false;
    sf::Font font;
    sf::Text boxText;
    sf::Text character;
    int index = 0;
    
    std::string dialogStrings[4] = {"You hear a loud noise coming from the vent.", "...", "eughh...", "gimme dat cock vro"};
    
    DialogBox();

    void iterate();

    void render(sf::RenderWindow &window);
};