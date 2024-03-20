#include <SFML/Graphics.hpp>
#ifndef OOP_GRID_H
#define OOP_GRID_H
#endif //OOP_GRID_H

class Grid {
private:
    sf::RenderWindow& window;
    const int size; // size of each square
    sf::RectangleShape square;
    static const sf::Color green;
    static const sf::Color yellow;
    static const sf::Color red;
    static const sf::Color blue;
    static const sf::Color light_yellow;
    static const sf::Color light_blue;
    static const sf::Color light_green;
    static const sf::Color light_red;

public:
    Grid() = default;
    Grid(sf::RenderWindow& window_, int size_) : window(window_), size(size_) {
        square.setSize(sf::Vector2f(size, size));
    }


    void draw_circle(int line1, int line2, int col1, int col2, sf::Color color);
    void draw();

    void setColor(int row, int col);

    void Position_flowers(int line, int col);

    void Position_yellow(int line, int col);

    void Position_red(int line, int col);

    void Position_green(int line, int col);

    void Position_blue(int line, int col);

};