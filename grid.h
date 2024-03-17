#include <SFML/Graphics.hpp>
#ifndef OOP_GRID_H
#define OOP_GRID_H
#endif //OOP_GRID_H

class Grid {
private:
    sf::RenderWindow& window;
    const int size; // size of each square
    sf::RectangleShape square;
    sf::Color green;
    sf::Color yellow;
    sf::Color red;
    sf::Color blue;
public:
    Grid() = default;
    Grid(sf::RenderWindow& window_, int size_, const sf::Color& g_, const sf::Color& y_, const sf::Color& r_, const sf::Color& b_) : window(window_), size(size_), green(g_), yellow(y_), red(r_), blue(b_) {
        square.setSize(sf::Vector2f(size, size));
    }


    void draw_circle(int line1, int line2, int col1, int col2, sf::Color color) {
        float minX = line1 * size;
        float maxX = line2 * size;
        float minY = col1 * size;
        float maxY = col2 * size;
        float centerX = (minX + maxX) / 2.0f;
        float centerY = (minY + maxY) / 2.0f;
        float radius = size / 2.0f;
        sf::CircleShape circle(radius);
        circle.setFillColor(color);
        circle.setPosition(centerX - radius, centerY - radius);
        window.draw(circle);

    }
    void draw() {
        for (int row = 0; row < 15; ++row) {
            for (int col = 0; col < 15; ++col) {
                setColor(row, col);
                square.setPosition(col * size, row * size);
                window.draw(square);
            }
        }
        draw_circle(1, 3, 1, 3, green);
        draw_circle(3, 5, 1, 3, green);
        draw_circle(1, 3, 3, 5, green);
        draw_circle(3, 5, 3, 5, green);

        draw_circle(10, 12, 1, 3, yellow);
        draw_circle(12, 14, 1, 3, yellow);
        draw_circle(10, 12, 3, 5, yellow);
        draw_circle(12, 14, 3, 5, yellow);

        draw_circle(1, 3, 10, 12, red);
        draw_circle(3, 5, 10, 12, red);
        draw_circle(1, 3, 12, 14, red);
        draw_circle(3, 5, 12, 14, red);

        draw_circle(10, 12, 10, 12, blue);
        draw_circle(12, 14, 10, 12, blue);
        draw_circle(10, 12, 12, 14, blue);
        draw_circle(12, 14, 12, 14, blue);

    }

    void setColor(int row, int col) {
        if ((row == 0 || row == 5) && col <= 5) {
            square.setFillColor(green); // green
        } else if ((col == 0 || col == 5) && (row >= 1 && row <= 4)) {
            square.setFillColor(green);
        } else if (row == 6 && col == 1) {
            square.setFillColor(green);
        } else if (row == 7 && (col >= 1 && col <= 5)) {
            square.setFillColor(green);
        } else if ((row == 0 || row == 5) && col >= 9) {
            square.setFillColor(yellow); // yellow
        } else if ((col == 9 || col == 14) && (row >= 1 && row <= 4)) {
            square.setFillColor(yellow);
        } else if (row == 1 && (col == 7 || col == 8)) {
            square.setFillColor(yellow);
        } else if (col == 7 && (row >= 2 && row <= 5)) {
            square.setFillColor(yellow);
        } else if ((row == 9 || row == 14) && col <= 5) {
            square.setFillColor(red); // red
        } else if ((col == 0 || col == 5) && (row >= 10 && row <= 13)) {
            square.setFillColor(red);
        } else if (row == 13 && col == 6) {
            square.setFillColor(red);
        } else if (col == 7 && (row >= 9 && row <= 13)) {
            square.setFillColor(red);
        } else if ((col == 9 || col == 14) && row >= 9) {
            square.setFillColor(blue); // blue
        } else if ((row == 9 || row == 14) && (col >= 10 && col <= 13)) {
            square.setFillColor(blue);
        } else if (row == 8 && col == 13) {
            square.setFillColor(blue);
        } else if (row == 7 && (col >= 9 && col < 14)) {
            square.setFillColor(blue);
        } else {
            square.setFillColor(sf::Color::White); // white
        }
    }
};
