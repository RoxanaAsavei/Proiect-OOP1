#include <iostream>
#include <fstream>
#include <utility>
#include "Token.h"


const int offset_ox = 480;
const int offset_oy = 60;
const int squareSize = 60;

// schimba pozitia curenta a tokenului
void Token::setPosition(sf::Vector2<float> newPosition) {
    this->shape.setPosition(newPosition);
    std::cout << "S-a actualizat pozitia\n";
}

void Token::renderToken(sf::RenderWindow &window) const {
    window.draw(this->shape);
}

/****
 * pozitii[index].first => linia
 * pozitii[index].second => coloana
 */

void Token::determinePos() { // 60 as the square size in the grid
    sf::Vector2<float> position;
    position.x = this->pozitii[index].second * 60 + offset_ox;
    position.y = this->pozitii[index].first * 60 + offset_oy;
    this->setPosition(position);
}

bool Token::final() const {
    return index == static_cast<int>(pozitii.size() - 1);
}

void Token::updatePos(int addOx, int addOy) {
    // adauga la pozitia curenta cei 2 parametri
    sf::Vector2f posCurrent = this->shape.getPosition();
    posCurrent.x += addOx;
    posCurrent.y += addOy;
    this->setPosition(posCurrent);

}

sf::Vector2 <float> Token::getShapePos() const {
    return this->shape.getPosition();
}

void Token::setShapeSize(sf::Vector2<float> dim) {
    this->shape.setSize(dim);
}

bool Token::clickedOn(sf::Vector2f& mousePos) {
    return this->shape.getGlobalBounds().contains(mousePos);
}

bool Token::immovable(int move) const{
    if(index >= startDrum and index <= finalDrum and
            (index + move > static_cast<int>(pozitii.size() - 1 ) or index + move == interzis))
        return true;
    return false;
}

bool Token::contains(std::pair<int, int> celula) const{
    return pozitii[index] == celula;
}

void Token::takeHome(sf::Vector2<float> pos) {
    this->setPosition(pos);
    this->index = -1;
    this->setShapeSize(sf::Vector2<float> {squareSize, squareSize});
}

std::pair<int, int> Token::getCoord() const{
    return this->pozitii[this->index];
}

void Token::setIndex(int val) {
    this->index = val;
}

bool Token::almostDone() const {
    return index >= startDrum && index <= finalDrum;
}

void Token::setPrevPos() {
    prevPos = pozitii[index];
}

void Token::move(int pas, bool &finished) {
    index += pas;
    if(index == static_cast<int>(pozitii.size() - 1))
        finished = true;
}

std::pair<int, int> Token::getPrev() {
    return prevPos;
}

Token::Token(std::string  color_, const sf::Texture* texture,
             std::vector<std::pair<int, int>> pozitii_) : pozitii(std::move(pozitii_)), color(std::move(color_)) {
    shape.setTexture(texture);
    index = -1;
    shape.setSize(sf::Vector2f(squareSize, squareSize));

}

