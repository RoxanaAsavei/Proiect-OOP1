#ifndef OOP_TOKEN_H
#define OOP_TOKEN_H
#include <SFML/Graphics.hpp>
#include "AssetsManager.h"

class Token {
public:
    sf::RectangleShape shape;
    int line;
    int col;
private:
    sf::Vector2f position;
    std::string color;

    // functions
    void initToken();

public:
    // constructor
    Token(const std::string &color_, AssetsManager &assetsManager);

    // functions
    void setPosition(sf::Vector2f newPosition);
    void renderToken(sf::RenderWindow &window) const;
    void determinePos();
    bool final() const;
};


#endif //OOP_TOKEN_H
