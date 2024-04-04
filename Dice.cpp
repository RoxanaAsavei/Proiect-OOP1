#include "Dice.h"

void Dice::initDiceFaces() {
    for(int i = 0; i < 6; ++i) {
        initFace(i);
        this->diceFaces.push_back(this->face);
    }

}

void Dice::initFace(int faceNo) {
    this->face.setSize(sf::Vector2f(size, size));
    this->face.setPosition(sf::Vector2f(1600, 450));
    this->face.setTexture(&this->textures[faceNo]);
}

Dice::Dice() {
    this->size = 150;
    this->textures.resize(6);
    this->diceValue = 3; // prima valoare, inainte sa dai cu zarul
    this->initTextures();
    this->initDiceFaces();
}

void Dice::Roll() { // returns a number between 0 and 5
    this->diceValue = rand() % 6;
}

void Dice::renderDice(sf::RenderWindow &window) {
    window.draw(this->diceFaces[this->diceValue]);
}

void Dice::initTextures() {
    this->textures[0].loadFromFile("dice sides/dice-six-faces-one.png");
    this->textures[1].loadFromFile("dice sides/dice-six-faces-two.png");
    this->textures[2].loadFromFile("dice sides/dice-six-faces-three.png");
    this->textures[3].loadFromFile("dice sides/dice-six-faces-four.png");
    this->textures[4].loadFromFile("dice sides/dice-six-faces-five.png");
    this->textures[5].loadFromFile("dice sides/dice-six-faces-six.png");


}

sf::RectangleShape Dice::getDiceFace() {
    return this->diceFaces[this->diceValue];
}

int Dice::getDiceValue() const {
    return this->diceValue;
}
