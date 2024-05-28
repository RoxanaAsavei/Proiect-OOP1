#ifndef OOP_DICE_H
#define OOP_DICE_H
#include<SFML/Graphics.hpp>
#include <random>

class Dice {
private:
    int diceValue;
    // for each face of the dice
    int size;
    sf::RectangleShape face;
    std::vector<sf::RectangleShape> diceFaces;
    std::vector<sf::Texture> textures;

    // for random number generator
    std::random_device rd;
    std::mt19937 mt;
    std::uniform_int_distribution<int>dist;

    // functions
    void initTextures(const std::string& color);
    void initDiceFaces();
    void initFace(int faceNo);

public:
    // constructor
    Dice();

    // accessors
    sf::RectangleShape getDiceFace();
    int getDiceValue() const;

    // functions
    void Roll();
    void initDice(const std::string& color);
    void renderDice(sf::RenderWindow &window);
};


#endif //OOP_DICE_H