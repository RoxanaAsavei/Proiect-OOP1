#ifndef OOP_DICE_H
#define OOP_DICE_H
#include<SFML/Graphics.hpp>

class Dice {
private:
    int diceValue;
    // for each face of the dice
    int size;
    sf::RectangleShape face;
    std::vector<sf::RectangleShape> diceFaces;
    std::vector<sf::Texture> textures;

    // functions
    void initTextures();
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
    void renderDice(sf::RenderWindow &window);
};


#endif //OOP_DICE_H