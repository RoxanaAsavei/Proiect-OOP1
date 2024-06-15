#include "Dice.h"


void Dice::initDiceFaces() {
    for(int i = 0; i < 6; ++i) {
        initFace(i);
        this->diceFaces.push_back(this->face);
    }

}

void Dice::initFace(int faceNo) {
    this->face.setSize(sf::Vector2f(size, size));
    this->face.setPosition(sf::Vector2f(1500, 450));
    this->face.setTexture(&this->textures[faceNo]);
}


void Dice::initDice(const std::string& color) {
    this->initTextures(color);
    this->initDiceFaces();
}

Dice::Dice() {
    this->size = 150;
    this->textures.resize(6);
    this->diceValue = 3; // prima valoare, inainte sa dai cu zarul


}

void Dice::Roll() { // returns a number between 0 and 5
    this->diceValue = rand() % 6;
}

void Dice::renderDice(sf::RenderWindow &window) {
    window.draw(this->diceFaces[this->diceValue]);
   // window.display();
}

void Dice::initTextures(const std::string& color) {
    std::string path;
    for(int i = 0; i < 6; ++i) {
        path = "assets/" + color + std::to_string(i + 1) + ".png";
        if(!this->textures[i].loadFromFile(path))
            throw textureError(path);
    }
}

sf::RectangleShape Dice::getDiceFace() {
    return this->diceFaces[this->diceValue];
}

int Dice::getDiceValue() const {
    return this->diceValue;
}

