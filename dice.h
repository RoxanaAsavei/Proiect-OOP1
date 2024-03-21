#ifndef OOP_DICE_H
#define OOP_DICE_H
#endif //OOP_DICE_H
#include <SFML/Graphics.hpp>
#include <ctime>

class Dice {
private:
    sf::RenderWindow& window;
    sf::RectangleShape face1;
    sf::RectangleShape face2;
    sf::RectangleShape face3;
    sf::RectangleShape face4;
    sf::RectangleShape face5;
    sf::RectangleShape face6;
    sf::Texture texture1;
    sf::Texture texture2;
    sf::Texture texture3;
    sf::Texture texture4;
    sf::Texture texture5;
    sf::Texture texture6;
    const int size;
public:
    Dice(sf::RenderWindow& window_, const int size_) : window(window_), size(size_) {
        // loading the textures for the six sides of the dice
        texture6.loadFromFile("Proiect-OOP1/dice sides/dice-six-faces-six.png");
        face6.setSize(sf::Vector2f(size, size));
        face6.setTexture(&texture6);

        texture5.loadFromFile("Proiect-OOP1/dice sides/dice-six-faces-five.png");
        face5.setSize(sf::Vector2f(size, size));
        face5.setTexture(&texture5);

        texture4.loadFromFile("Proiect-OOP1/dice sides/dice-six-faces-four.png");
        face4.setSize(sf::Vector2f(size, size));
        face4.setTexture(&texture4);

        texture3.loadFromFile("Proiect-OOP1/dice sides/dice-six-faces-three.png");
        face3.setSize(sf::Vector2f(size, size));
        face3.setTexture(&texture3);

        texture2.loadFromFile("Proiect-OOP1/dice sides/dice-six-faces-two.png");
        face2.setSize(sf::Vector2f(size, size));
        face2.setTexture(&texture2);

        texture1.loadFromFile("Proiect-OOP1/dice sides/dice-six-faces-one.png");
        face1.setSize(sf::Vector2f(size, size));
        face1.setTexture(&texture1);

    }
public:
    int Roll() {
        srand(static_cast<unsigned int>(time(0)));
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
