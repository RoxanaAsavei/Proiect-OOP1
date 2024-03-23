#include "Dice.h"



void Dice::initDiceFaces() {
    for(int i = 0; i < 6; ++i) {
        initFace(i);
        this->diceFaces.push_back(this->face);
    }

}

void Dice::initFace(int faceNo) {
    this->face.setSize(sf::Vector2f(size, size));
    this->face.setPosition(sf::Vector2f(10* 60, 10 * 60)); // line 10, col 10
    this->face.setTexture(&this->textures[faceNo]);
}

Dice::Dice() {
    this->size = 100;
    this->diceValue = 0;
    this->textures.resize(6);
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
    this->textures[0].loadFromFile("Proiect-OOP1/dice sides/dice-six-faces-one.png");
    this->textures[1].loadFromFile("Proiect-OOP1/dice sides/dice-six-faces-two.png");
    this->textures[2].loadFromFile("Proiect-OOP1/dice sides/dice-six-faces-three.png");
    this->textures[3].loadFromFile("Proiect-OOP1/dice sides/dice-six-faces-four.png");
    this->textures[4].loadFromFile("Proiect-OOP1/dice sides/dice-six-faces-five.png");
    this->textures[5].loadFromFile("Proiect-OOP1/dice sides/dice-six-faces-six.png");


}
