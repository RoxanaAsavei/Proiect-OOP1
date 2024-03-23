#ifndef OOP_DICE_H
#define OOP_DICE_H
#include<SFML/Graphics.hpp>

class Dice {
public:
    int diceValue;
private:
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

    // functions
    void Roll();
    void renderDice(sf::RenderWindow &window);
};


#endif //OOP_DICE_H
