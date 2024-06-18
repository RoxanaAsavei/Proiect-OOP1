#ifndef OOP_DICE_H
#define OOP_DICE_H
#include<SFML/Graphics.hpp>
#include "Exceptions.h"
#include <random>

class Dice {
private:
    int diceValue;
    // for each face of the dice
    int size;
    sf::RectangleShape face;
    std::vector<sf::RectangleShape> diceFaces;

    // for random number generator
    std::random_device rd;
    std::mt19937 mt;
    std::uniform_int_distribution<int>dist;

    // functions
    void initFace(sf::Texture* texture);

public:
    // constructor
    Dice();


    // accessors
    sf::RectangleShape getDiceFace();
    int getDiceValue() const;

    // functions
    void initDiceFaces(std::vector<sf::Texture>& textures);
    void Roll();
    void renderDice(sf::RenderWindow &window);
};


#endif //OOP_DICE_H