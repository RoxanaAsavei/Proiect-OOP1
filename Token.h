#ifndef OOP_TOKEN_H
#define OOP_TOKEN_H
#include <SFML/Graphics.hpp>

class Token {
public:
    sf::RectangleShape shape;
    int line;
    int col;
private:
    sf::Vector2f position;
    sf::Texture texture;
    std::string color;

    // functions
    void initToken();
    void initTexture();

public:
    // constructor
    explicit Token(const std::string &color_);

    // functions
    void setPosition(sf::Vector2f newPosition);
    void renderToken(sf::RenderWindow &window) const;
    void determinePos();
    void move(int value, bool &finished);
    bool final() const;

};


#endif //OOP_TOKEN_H
