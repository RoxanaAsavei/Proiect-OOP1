#ifndef OOP_DICE_H
#define OOP_DICE_H
#endif //OOP_DICE_H
#include <SFML/Graphics.hpp>

class Dice {
private:
    sf::RectangleShape face1;
    sf::RectangleShape face2;
    sf::RectangleShape face3;
    sf::RectangleShape face4;
    sf::RectangleShape face5;
    sf::RectangleShape face6;
    const int size;
public:
    Dice(const int size_) : size(size_) {
        // loading the textures for the six sides of the dice
        sf::Texture texture;

        texture.loadFromFile("C:\\Users\\roxan\\OneDrive\\Desktop\\proiect poo\\Proiect-OOP1\\dice sides\\dice-six-faces-six.png");
        face6.setSize(sf::Vector2f(size, size));
        face6.setTexture(&texture);

        texture.loadFromFile("C:\\Users\\roxan\\OneDrive\\Desktop\\proiect poo\\Proiect-OOP1\\dice sides\\dice-six-faces-five.png");
        face5.setSize(sf::Vector2f(size, size));
        face5.setTexture(&texture);

        texture.loadFromFile("C:\\Users\\roxan\\OneDrive\\Desktop\\proiect poo\\Proiect-OOP1\\dice sides\\dice-six-faces-four.png");
        face4.setSize(sf::Vector2f(size, size));
        face4.setTexture(&texture);

        texture.loadFromFile("C:\\Users\\roxan\\OneDrive\\Desktop\\proiect poo\\Proiect-OOP1\\dice sides\\dice-six-faces-three.png");
        face3.setSize(sf::Vector2f(size, size));
        face3.setTexture(&texture);

        texture.loadFromFile("C:\\Users\\roxan\\OneDrive\\Desktop\\proiect poo\\Proiect-OOP1\\dice sides\\dice-six-faces-two.png");
        face2.setSize(sf::Vector2f(size, size));
        face2.setTexture(&texture);

        texture.loadFromFile("C:\\Users\\roxan\\OneDrive\\Desktop\\proiect poo\\Proiect-OOP1\\dice sides\\dice-six-faces-one.png");
        face1.setSize(sf::Vector2f(size, size));
        face1.setTexture(&texture);

    }


};
