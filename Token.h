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
    // compulsory requirements
    Token(const std::string &color_, AssetsManager &assetsManager);
    ~Token();
    // constructor de copiere
    Token(const Token& other);
    // op =
    Token& operator =(const Token& other);
    // op <<
    friend std::ostream& operator <<(std::ostream& os, const Token& token);

    // functions
    void setPosition(sf::Vector2f newPosition);
    void renderToken(sf::RenderWindow &window) const;
    void determinePos();
    bool final() const;
    void updatePos(int addOx, int addOy);
};


#endif //OOP_TOKEN_H