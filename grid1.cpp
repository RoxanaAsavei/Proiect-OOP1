#include "grid1.h"

const sf::Color Grid::green{60,179,113};
const sf::Color Grid::yellow{255, 255, 0};
const sf::Color Grid::red{220, 20, 60};
const sf::Color Grid::blue{0, 191, 255};
const sf::Color Grid::light_yellow{253, 253, 150};
const sf::Color Grid::light_blue{137, 207, 240};
const sf::Color Grid::light_green{175, 225, 175};
const sf::Color Grid::light_red{222, 49, 99};

void Grid::setColor(int line, int col, sf::RectangleShape &square) {
    if ((line == 0 || line == 5) && col <= 5) {
        square.setFillColor(green); // green
    } else if ((col == 0 || col == 5) && (line >= 1 && line <= 4)) {
        square.setFillColor(green);
    } else if (line == 6 && col == 1) {
        square.setFillColor(green);
    } else if (line == 7 && (col >= 1 && col <= 5)) {
        square.setFillColor(green);
    } else if ((line == 0 || line == 5) && col >= 9) {
        square.setFillColor(yellow); // yellow
    } else if ((col == 9 || col == 14) && (line >= 1 && line <= 4)) {
        square.setFillColor(yellow);
    } else if (line == 1 && (col == 7 || col == 8)) {
        square.setFillColor(yellow);
    } else if (col == 7 && (line >= 2 && line <= 5)) {
        square.setFillColor(yellow);
    } else if ((line == 9 || line == 14) && col <= 5) {
        square.setFillColor(red); // red
    } else if ((col == 0 || col == 5) && (line >= 10 && line <= 13)) {
        square.setFillColor(red);
    } else if (line == 13 && col == 6) {
        square.setFillColor(red);
    } else if (col == 7 && (line >= 9 && line <= 13)) {
        square.setFillColor(red);
    } else if ((col == 9 || col == 14) && line >= 9) {
        square.setFillColor(blue); // blue
    } else if ((line == 9 || line == 14) && (col >= 10 && col <= 13)) {
        square.setFillColor(blue);
    } else if (line == 8 && col == 13) {
        square.setFillColor(blue);
    }
    else if (line == 7 && (col >= 9 && col < 14)) {
        square.setFillColor(blue);
    }
    else if((line >= 6 && line <= 8) && (col >= 6 && col <= 8)) {
        square.setFillColor(sf::Color::White);
    }
    else {
        square.setFillColor(sf::Color(210, 180, 140)); // beige
    }
}



void Grid::initCircle(int line1, int line2, int col1, int col2, sf::Color color, sf::CircleShape &circle) {
    // setting dimension, color and position for the circle
    float minX = line1 * this->size;
    float maxX = line2 * this->size;
    float minY = col1 * this->size;
    float maxY = col2 * this->size;
    float centerX = (minX + maxX) / 2.0f;
    float centerY = (minY + maxY) / 2.0f;
    float radius = this->size / 2.0f;
    circle.setRadius(radius);
    circle.setFillColor(color);
    circle.setPosition(centerX - radius, centerY - radius);
}


void Grid::initSquare(int line, int col, sf::RectangleShape& square) {
    // setting the square's properties
    square.setSize(sf::Vector2f(size, size));
    setColor(line, col, square);
    square.setPosition(col * size, line * size);
    square.setOutlineThickness(1.0f);
    square.setOutlineColor(sf::Color::Black);
}



void Grid::initCircles() {

    sf::CircleShape g1;
    this->initCircle(1, 3, 1, 3, light_green, g1);
    this->circles.push_back(g1);

    sf::CircleShape g2;
    this->initCircle(3, 5, 1, 3, light_green, g2);
    this->circles.push_back(g2);

    sf::CircleShape g3;
    this->initCircle(1, 3, 3, 5, light_green, g3);
    this->circles.push_back(g3);

    sf::CircleShape g4;
    this->initCircle(3, 5, 3, 5, light_green, g4);
    this->circles.push_back(g4);

    sf::CircleShape y1;
    this->initCircle(10, 12, 1, 3, light_yellow, y1);
    this->circles.push_back(y1);

    sf::CircleShape y2;
    this->initCircle(12, 14, 1, 3, light_yellow, y2);
    this->circles.push_back(y2);

    sf::CircleShape y3;
    this->initCircle(10, 12, 3, 5, light_yellow, y3);
    this->circles.push_back(y3);

    sf::CircleShape y4;
    this->initCircle(12, 14, 3, 5, light_yellow, y4);
    this->circles.push_back(y4);

    sf::CircleShape r1;
    this->initCircle(1, 3, 10, 12, light_red, r1);
    this->circles.push_back(r1);

    sf::CircleShape r2;
    this->initCircle(3, 5, 10, 12, light_red, r2);
    this->circles.push_back(r2);

    sf::CircleShape r3;
    this->initCircle(1, 3, 12, 14, light_red, r3);
    this->circles.push_back(r3);

    sf::CircleShape r4;
    this->initCircle(3, 5, 12, 14, light_red, r4);
    this->circles.push_back(r4);

    sf::CircleShape b1;
    this->initCircle(10, 12, 10, 12, light_blue, b1);
    this->circles.push_back(b1);

    sf::CircleShape b2;
    this->initCircle(12, 14, 10, 12, light_blue, b2);
    this->circles.push_back(b2);

    sf::CircleShape b3;
    this->initCircle(10, 12, 12, 14, light_blue, b3);
    this->circles.push_back(b3);

    sf::CircleShape b4;
    this->initCircle(12, 14, 12, 14, light_blue, b4);
    this->circles.push_back(b4);

}

void Grid::initTiles() {
    // Initialize tiles vector with size 15x15
    tiles.resize(15);
    for (int i = 0; i < 15; ++i) {
        tiles[i].resize(15);
    }

    for(int line = 0; line < 15; ++line) { // for each tile
        for(int col = 0; col < 15; ++col) {
            sf::RectangleShape square; // Create a new square object
            this->initSquare(line, col, square); // setting the square
            this->tiles[line][col] = square;
        }
    }
}


Grid::Grid() {
    this->size = 60;
    initTiles();
    initCircles();
}

void Grid::renderGrid(sf::RenderWindow &window) {
    // rendering the tiles
    for(int i = 0; i < 15; ++i) {
        for(int j = 0; j < 15; ++j) {
            window.draw(this->tiles[i][j]);
        }
    }
    // rendering the circles
    for(auto c : this->circles) {
        window.draw(c);
    }


}


