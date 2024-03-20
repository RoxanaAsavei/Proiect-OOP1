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
    sf::Color light_yellow;
    sf::Color light_blue;
    sf::Color light_green;
    sf::Color light_red;

public:
    Grid() = default;
    Grid(sf::RenderWindow& window_, int size_, const sf::Color& g_, const sf::Color& y_, const sf::Color& r_,
         const sf::Color& b_, const sf::Color& lg_, const sf::Color& ly_, const sf::Color& lr_, const sf::Color& lb_)
         : window(window_), size(size_), green(g_), yellow(y_), red(r_), blue(b_), light_yellow(ly_), light_blue(lb_),
         light_green(lg_), light_red(lr_) {
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
                square.setOutlineThickness(1.0f);
                square.setOutlineColor(sf::Color::Black);
                window.draw(square);
            }
        }
        draw_circle(1, 3, 1, 3, light_green);
        draw_circle(3, 5, 1, 3, light_green);
        draw_circle(1, 3, 3, 5, light_green);
        draw_circle(3, 5, 3, 5, light_green);

        draw_circle(10, 12, 1, 3, light_yellow);
        draw_circle(12, 14, 1, 3, light_yellow);
        draw_circle(10, 12, 3, 5, light_yellow);
        draw_circle(12, 14, 3, 5, light_yellow);

        draw_circle(1, 3, 10, 12, light_red);
        draw_circle(3, 5, 10, 12, light_red);
        draw_circle(1, 3, 12, 14, light_red);
        draw_circle(3, 5, 12, 14, light_red);

        draw_circle(10, 12, 10, 12, light_blue);
        draw_circle(12, 14, 10, 12, light_blue);
        draw_circle(10, 12, 12, 14, light_blue);
        draw_circle(12, 14, 12, 14, light_blue);

        Position_yellow(10, 1);
        Position_yellow(12, 1);
        Position_yellow(10, 3);
        Position_yellow(12, 3);

        Position_green(1, 1);
        Position_green(3, 1);
        Position_green(1, 3);
        Position_green(3, 3);

        Position_blue(10,10);
        Position_blue(12, 10);
        Position_blue(10, 12);
        Position_blue(12, 12);

        Position_red(1, 10);
        Position_red(3, 10);
        Position_red(1, 12);
        Position_red(3, 12);

        for(int i = 6; i <= 8; ++i) {
            for(int j = 6; j <= 8; ++j) {
                Position_flowers(i, j);
            }
        }

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
        }
        else if (row == 7 && (col >= 9 && col < 14)) {
            square.setFillColor(blue);
        }
        /*
        else if((row >= 6 && row <= 8) && (col >= 6 && col <= 8)) {
            // square.setFillColor(sf::Color::Black);
            sf::Texture corner;
            corner.loadFromFile("C:\\Users\\roxan\\OneDrive\\Desktop\\proiect poo\\Proiect-OOP1\\fundal.jpg");
            square.setTexture(&corner);
        } */
        else {
            square.setFillColor(sf::Color(210, 180, 140)); // beige
        }
    }
/*
    friend void Position_yellow(sf::RenderWindow& window, int size, int line, int col);
    friend void Position_red(sf::RenderWindow& window, int size, int line, int col);
    friend void Position_green(sf::RenderWindow& window, int size, int line, int col);
    friend void Position_blue(sf::RenderWindow& window, int size, int line, int col);
*/

    void Position_flowers(int line, int col) {
        sf::Texture texture;
        texture.loadFromFile("C:\\Users\\roxan\\OneDrive\\Desktop\\proiect poo\\Proiect-OOP1\\fundal.jpg");
        square.setTexture(&texture);
        square.setPosition(col * size, line * size);
        square.setOutlineColor(sf::Color::Transparent);
        window.draw(square);
    }

    void Position_yellow(int line, int col) {
        sf::Texture yellow_token;
        yellow_token.loadFromFile("C:\\Users\\roxan\\OneDrive\\Desktop\\proiect poo\\Proiect-OOP1\\tokens\\yellow_token.png");
        sf::Sprite yellow1(yellow_token);
        yellow1.setScale(0.2f, 0.2f);
        yellow1.setPosition(line * size - 4, col * size);
        window.draw(yellow1);
    }

    void Position_red(int line, int col) {
        sf::Texture red_token;
        red_token.loadFromFile("C:\\Users\\roxan\\OneDrive\\Desktop\\proiect poo\\Proiect-OOP1\\tokens\\red_token.png");
        sf::Sprite red1(red_token);
        red1.setScale(0.2f, 0.2f);
        red1.setPosition(line * size - 4, col * size);
        window.draw(red1);
    }

    void Position_green(int line, int col) {
        sf::Texture green_token;
        green_token.loadFromFile("C:\\Users\\roxan\\OneDrive\\Desktop\\proiect poo\\Proiect-OOP1\\tokens\\green_token.png");
        sf::Sprite green1(green_token);
        green1.setScale(0.2f, 0.2f);
        green1.setPosition(line * size - 4, col * size);
        window.draw(green1);
    }

    void Position_blue(int line, int col) {
        sf::Texture blue_token;
        blue_token.loadFromFile("C:\\Users\\roxan\\OneDrive\\Desktop\\proiect poo\\Proiect-OOP1\\tokens\\blue_token.png");
        sf::Sprite blue1(blue_token);
        blue1.setScale(0.2f, 0.2f);
        blue1.setPosition(line * size - 4, col * size);
        window.draw(blue1);
    }

};