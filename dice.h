#ifndef OOP_DICE_H
#define OOP_DICE_H
#endif //OOP_DICE_H
#include <SFML/Graphics.hpp>

class Dice {
private:
    sf::RenderWindow& window;
    sf::RectangleShape face1;
    sf::RectangleShape face2;
    sf::RectangleShape face3;
    sf::RectangleShape face4;
    sf::RectangleShape face5;
    sf::RectangleShape face6;
    const int size;
public:
    Dice(sf::RenderWindow& window_, const int size_) : window(window_), size(size_) {
        // loading the textures for the six sides of the dice
        sf::Texture texture;

        texture.loadFromFile("Proiect-OOP1/dice sides/dice-six-faces-six.png");
        face6.setSize(sf::Vector2f(size, size));
        face6.setTexture(&texture);

        texture.loadFromFile("Proiect-OOP1/dice sides/dice-six-faces-five.png");
        face5.setSize(sf::Vector2f(size, size));
        face5.setTexture(&texture);

        texture.loadFromFile("Proiect-OOP1/dice sides/dice-six-faces-four.png");
        face4.setSize(sf::Vector2f(size, size));
        face4.setTexture(&texture);

        texture.loadFromFile("Proiect-OOP1/dice sides/dice-six-faces-three.png");
        face3.setSize(sf::Vector2f(size, size));
        face3.setTexture(&texture);

        texture.loadFromFile("Proiect-OOP1/dice sides/dice-six-faces-two.png");
        face2.setSize(sf::Vector2f(size, size));
        face2.setTexture(&texture);

        texture.loadFromFile("Proiect-OOP1/dice sides/dice-six-faces-one.png");
        face1.setSize(sf::Vector2f(size, size));
        face1.setTexture(&texture);

    }
public:
    int Roll() { // tb facuta uniform distribuita si randomizat seed
        return rand() % 6 + 1;
    }

    void Display() {
        int roll_value = Roll();
        if(roll_value == 1) {
            window.draw(face1);
        }
        else if(roll_value == 2) {
            window.draw(face2);
        }
        else if(roll_value == 3) {
            window.draw(face3);
        }
        else if(roll_value == 4) {
            window.draw(face4);
        }
        else if(roll_value == 5) {
            window.draw(face5);
        }
        else {
            window.draw(face6);
        }
    }

};
