#include <iostream>
#include "Token.h"
#include "AssetsManager.h"

const int offset_ox = 480;
const int offset_oy = 60;

void Token::setPosition(sf::Vector2 <float> newPosition) {
    this->shape.setPosition(newPosition);
}

void Token::initToken() {
    this->line = 0;
    this->col = 0;
    this->shape.setSize(sf::Vector2f(60, 60));
}


Token::Token(const std::string &color_, AssetsManager &assetsManager) : color(color_) {
    initToken();
    if(this->color == "red") {
        this->shape.setTexture(assetsManager.getRed());
    }
    else if(this->color == "blue") {
        this->shape.setTexture(assetsManager.getBlue());
    }
    else if(this->color == "green") {
        this->shape.setTexture(assetsManager.getGreen());
    }
    else { // yellow
        this->shape.setTexture(assetsManager.getYellow());
    }

}

void Token::renderToken(sf::RenderWindow &window) const {
    window.draw(this->shape);
}

void Token::determinePos() { // 60 as the square size in the grid
    this->position.x = this->col * 60 + offset_ox;
    this->position.y = this->line * 60 + offset_oy;
    this->shape.setPosition(this->position.x, this->position.y);
}

bool Token::final() const {
    return this->line == 7 && this->col == 7;
}

void Token::updatePos(int addOx, int addOy) {
    // adauga la pozitia curenta cei 2 parametri
    sf::Vector2f posCurrent = this->shape.getPosition();
    posCurrent.x += addOx;
    posCurrent.y += addOy;
    this->setPosition(posCurrent);

}

Token::~Token() {
    std::cout << "Token destroyed\n";
}

std::ostream &operator<<(std::ostream &os, const Token &token) {
    os << "Line: " << token.line << "\n";
    os << "Column: " << token.col << "\n";
    os << "Position: " << token.position.x << " " << token.position.y << "\n";
    os << "Color: " << token.color << "\n";
    return os;
}

Token &Token::operator=(const Token &other) {
    this->shape = other.shape;
    this->line = other.line;
    this->col = other.col;
    this->position = other.position;
    this->color = other.color;
    std::cout << "Op =\n";
    return *this;
}

Token::Token(const Token &other) : shape(other.shape), line(other.line), col(other.col),
                                   position(other.position), color(other.color){
    std::cout << "Token copied\n";
}

sf::Vector2 <float> Token::getShapePos() const {
    return this->shape.getPosition();
}

int Token::getLine() const {
    return this->line;
}

int Token::getCol() const {
    return this->col;
}

void Token::setLine(int line_) {
    this->line = line_;
}

void Token::setCol(int col_) {
    this->col = col_;
}

void Token::setShapeSize(sf::Vector2<float> dim) {
    this->shape.setSize(dim);
}

bool Token::clickedOn(sf::Vector2f& mousePos) {
    return this->shape.getGlobalBounds().contains(mousePos);
}
