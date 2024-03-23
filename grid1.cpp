#include "grid1.h"

const sf::Color Grid::green{60,179,113};
const sf::Color Grid::yellow{255, 255, 0};
const sf::Color Grid::red{220, 20, 60};
const sf::Color Grid::blue{0, 191, 255};
const sf::Color Grid::light_yellow{253, 253, 150};
const sf::Color Grid::light_blue{137, 207, 240};
const sf::Color Grid::light_green{175, 225, 175};
const sf::Color Grid::light_red{222, 49, 99};

void Grid::setColor(int line, int col) {
    if ((line == 0 || line == 5) && col <= 5) {
        this->square.setFillColor(green); // green
    } else if ((col == 0 || col == 5) && (line >= 1 && line <= 4)) {
        this->square.setFillColor(green);
    } else if (line == 6 && col == 1) {
        this->square.setFillColor(green);
    } else if (line == 7 && (col >= 1 && col <= 5)) {
        this->square.setFillColor(green);
    } else if ((line == 0 || line == 5) && col >= 9) {
        this->square.setFillColor(yellow); // yellow
    } else if ((col == 9 || col == 14) && (line >= 1 && line <= 4)) {
        this->square.setFillColor(yellow);
    } else if (line == 1 && (col == 7 || col == 8)) {
        this->square.setFillColor(yellow);
    } else if (col == 7 && (line >= 2 && line <= 5)) {
        this->square.setFillColor(yellow);
    } else if ((line == 9 || line == 14) && col <= 5) {
        this->square.setFillColor(red); // red
    } else if ((col == 0 || col == 5) && (line >= 10 && line <= 13)) {
        this->square.setFillColor(red);
    } else if (line == 13 && col == 6) {
        this->square.setFillColor(red);
    } else if (col == 7 && (line >= 9 && line <= 13)) {
        this->square.setFillColor(red);
    } else if ((col == 9 || col == 14) && line >= 9) {
        this->square.setFillColor(blue); // blue
    } else if ((line == 9 || line == 14) && (col >= 10 && col <= 13)) {
        this->square.setFillColor(blue);
    } else if (line == 8 && col == 13) {
        this->square.setFillColor(blue);
    }
    else if (line == 7 && (col >= 9 && col < 14)) {
        this->square.setFillColor(blue);
    }
    else if((line >= 6 && line <= 8) && (col >= 6 && col <= 8)) {
        this->square.setFillColor(sf::Color::White);
    }
    else {
        this->square.setFillColor(sf::Color(210, 180, 140)); // beige
    }
}



void Grid::initCircle(int line1, int col1, int line2, int col2, sf::Color color) {
    // setting dimension, color and position for the circle
    float minX = line1 * size;
    float maxX = line2 * size;
    float minY = col1 * size;
    float maxY = col2 * size;
    float centerX = (minX + maxX) / 2.0f;
    float centerY = (minY + maxY) / 2.0f;
    float radius = size / 2.0f;
    this->circle.setFillColor(color);
    this->circle.setPosition(centerX - radius, centerY - radius);
}

void Grid::initSquare(int line, int col) {
    // setting the square's properties
    this->size = 60;
    this->square.setSize(sf::Vector2f(size, size));
    setColor(line, col);
    this->square.setPosition(col * size, line * size);
    this->square.setOutlineThickness(1.0f);
    this->square.setOutlineColor(sf::Color::Black);

}


void Grid::initCircles() {
    this->initCircle(1, 3, 1, 3, light_green);
    this->circles.push_back(this->circle);
    this->initCircle(3, 5, 1, 3, light_green);
    this->circles.push_back(this->circle);
    this->initCircle(1, 3, 3, 5, light_green);
    this->circles.push_back(this->circle);
    this->initCircle(3, 5, 3, 5, light_green);
    this->circles.push_back(this->circle);

    this->initCircle(10, 12, 1, 3, light_yellow);
    this->circles.push_back(this->circle);
    this->initCircle(12, 14, 1, 3, light_yellow);
    this->circles.push_back(this->circle);
    this->initCircle(10, 12, 3, 5, light_yellow);
    this->circles.push_back(this->circle);
    this->initCircle(12, 14, 3, 5, light_yellow);
    this->circles.push_back(this->circle);

    this->initCircle(1, 3, 10, 12, light_red);
    this->circles.push_back(this->circle);
    this->initCircle(3, 5, 10, 12, light_red);
    this->circles.push_back(this->circle);
    this->initCircle(1, 3, 12, 14, light_red);
    this->circles.push_back(this->circle);
    this->initCircle(3, 5, 12, 14, light_red);
    this->circles.push_back(this->circle);

    this->initCircle(10, 12, 10, 12, light_blue);
    this->circles.push_back(this->circle);
    this->initCircle(12, 14, 10, 12, light_blue);
    this->circles.push_back(this->circle);
    this->initCircle(10, 12, 12, 14, light_blue);
    this->circles.push_back(this->circle);
    this->initCircle(12, 14, 12, 14, light_blue);
    this->circles.push_back(this->circle);

}

void Grid::initTiles() {
    // Initialize tiles vector with size 15x15
    tiles.resize(15);
    for (int i = 0; i < 15; ++i) {
        tiles[i].resize(15);
    }

    for(int line = 0; line < 15; ++line) { // for each tile
        for(int col = 0; col < 15; ++col) {
            this->initSquare(line, col); // setting the square
            this->tiles[line].push_back(this->square); // appending the square
        }
    }
}

Grid::Grid() {
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
    for(auto const &c : this->circles) {
        window.draw(c);
    }
}


