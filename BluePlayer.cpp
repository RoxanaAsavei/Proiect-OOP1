#include "BluePlayer.h"
const int offset_ox = 480;
const int offset_oy = 60;
const int squareSize = 60;

void BluePlayer::initPlayer() {
    this->color = "blue";
    // adding all 4 tokens
    Token token1{this->color, this->assetsManager};
    // setting position for the in-house tokens
    token1.setPosition(sf::Vector2f(10 * squareSize  + squareSize / 2 + offset_ox, 10 * squareSize  + offset_oy));
    this->tokensInHouse.push_back(token1);
    this->takenPositions.push_back(token1.getShapePos());

    Token token2{this->color, this->assetsManager};
    token2.setPosition(sf::Vector2f(12 * squareSize  + squareSize / 2 + offset_ox, 10 * squareSize  + offset_oy));
    this->tokensInHouse.push_back(token2);
    this->takenPositions.push_back(token2.getShapePos());

    Token token3{this->color, this->assetsManager};
    token3.setPosition(sf::Vector2f(10 * squareSize + squareSize / 2 + offset_ox, 12 * squareSize + offset_oy));
    this->tokensInHouse.push_back(token3);
    this->takenPositions.push_back(token3.getShapePos());

    Token token4{this->color, this->assetsManager};
    token4.setPosition(sf::Vector2f(12 * squareSize + squareSize / 2 + offset_ox, 12 * squareSize + offset_oy));
    this->tokensInHouse.push_back(token4);
    this->takenPositions.push_back(token4.getShapePos());

    sf::RectangleShape square;
    square.setSize(sf::Vector2f(squareSize, squareSize));
    square.setFillColor(sf::Color::White);
    square.setOutlineColor(sf::Color::Blue);
    square.setOutlineThickness(2.0f);
    square.setPosition(1500, 720);
    this->finishTiles.push_back(square);
    square.setPosition(1560, 720);
    this->finishTiles.push_back(square);
    square.setPosition(1500, 780);
    this->finishTiles.push_back(square);
    square.setPosition(1560, 780);
    this->finishTiles.push_back(square);
}

BluePlayer::BluePlayer() {
    this->initPlayer();
    this->dice.initDice(color);
}






