#include "Dice.h"


void Dice::initDiceFaces(std::vector<sf::Texture>& textures) {
    for(int i = 0; i < 6; ++i) {
        initFace(&textures[i]);
        this->diceFaces.push_back(this->face);
    }

}

void Dice::initFace(sf::Texture* texture) {
    this->face.setSize(sf::Vector2f(size, size));
    this->face.setPosition(sf::Vector2f(1500, 450));
    this->face.setTexture(texture);
}


Dice::Dice() {
    this->size = 150;
    this->diceValue = 3; // prima valoare, inainte sa dai cu zarul

}

void Dice::Roll() { // returns a number between 0 and 5
    this->diceValue = rand() % 6;
}

void Dice::renderDice(sf::RenderWindow &window) {
    window.draw(this->diceFaces[this->diceValue]);
}


sf::RectangleShape Dice::getDiceFace() {
    return this->diceFaces[this->diceValue];
}

int Dice::getDiceValue() const {
    return this->diceValue;
}

