#include <dialogbox.hpp>
#include <textureManager.hpp>

DialogBox::DialogBox() {
    for (int i = 0; i < 3; i++) {
        std::string name = "dialogbox" + std::to_string(i);
        std::string path = "assets/dialogbox" + std::to_string(i) + ".png";
        dialogBoxTextures[i] = TextureManager::loadTexture(name, path);
        dialogBoxSprite.setTexture(*dialogBoxTextures[0]);
        dialogBoxSprite.setScale(0.9, 0.9);
        dialogBoxSprite.setPosition(170, 170); 
    }
    

    font.loadFromFile("C:/Users/johns/Downloads/dogica/TTF/dogica.ttf");
    boxText.setFont(font);
    boxText.setCharacterSize(15); // in pixels, not points
    boxText.setFillColor(sf::Color::White);
    boxText.setString(dialogStrings[0]);
    boxText.setPosition(240, 560);

    character.setFont(font);
    character.setCharacterSize(20); // in pixels, not points
    character.setFillColor(sf::Color::White);
    character.setString("You");
    character.setPosition(240, 510);
};

void DialogBox::iterate() {
    index++;
    if (index > 0 && index != 2) {
        std::string name = "dialogbox" + std::to_string(index);
        character.setString("???");
        dialogBoxSprite.setTexture(*(TextureManager::textureMap[name]));
    }

    if (index == 3) {
        std::string name = "dialogbox" + std::to_string(index - 1);
        character.setString("edging enthusiast");
        dialogBoxSprite.setTexture(*(TextureManager::textureMap[name]));
    }

    if (index < 4) {
        boxText.setString(dialogStrings[index]);
    }
}

void DialogBox::render(sf::RenderWindow &window) {
    window.draw(dialogBoxSprite);
    window.draw(boxText);
    window.draw(character);
};