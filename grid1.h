#include <SFML/Graphics.hpp>
#ifndef OOP_GRID_H
#define OOP_GRID_H
#endif //OOP_GRID_H

class Grid {
private:
    // class objects
    int size; // size of each square
    std::vector<std::vector<sf::RectangleShape>> tiles;
    std::vector<sf::CircleShape> circles;

    // colors for the grid
    static const sf::Color green;
    static const sf::Color yellow;
    static const sf::Color red;
    static const sf::Color blue;
    static const sf::Color light_yellow;
    static const sf::Color light_blue;
    static const sf::Color light_green;
    static const sf::Color light_red;

    // functions
    void initCircle(int line1, int line2, int col1, int col2, sf::Color color, sf::CircleShape &circle);
    void initCircles();

    static void setColor(int row, int col, sf::RectangleShape &square);
    void initSquare(int line, int col, sf::RectangleShape &square);
    void initTiles();


public:
    // constructor
    Grid();

    // functions
    void renderGrid(sf::RenderWindow &window);


};