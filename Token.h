#ifndef OOP_TOKEN_H
#define OOP_TOKEN_H
#include <SFML/Graphics.hpp>
#include "AssetsManager.h"

class Token {
private:
    sf::RectangleShape shape;
    std::vector <std::pair<int, int>> pozitii;
    int index; // pozitia la care ma aflu in vect pozitii
    std::string color;
    static const int startDrum = 50;
    static const int finalDrum = 55;
    static const int interzis = 56;
    std::pair<int, int> prevPos;
    // functions
    void initToken();

public:
    // compulsory requirements
    Token(const std::string &color_, AssetsManager &assetsManager);

    // functions
    void setPosition(sf::Vector2<float> newPosition);
    void renderToken(sf::RenderWindow &window) const;
    void determinePos();
    bool final() const;
    void updatePos(int addOx, int addOy);
    sf::Vector2f getShapePos() const;
    void setShapeSize(sf::Vector2<float> dim);
    bool clickedOn(sf::Vector2f& mousePos);
    bool immovable(int move) const;
    bool contains(std::pair<int, int> celula) const;
    void takeHome(sf::Vector2<float> pos);
    std::pair<int, int> getCoord() const;
    void setIndex(int val);
    bool almostDone();
    void setPrevPos();
    void move(int pas, bool& finished);
    std::pair<int, int> getPrev();
};


#endif //OOP_TOKEN_H