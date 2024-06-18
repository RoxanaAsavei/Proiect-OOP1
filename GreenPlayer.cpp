#include "GreenPlayer.h"

const int offset_ox = 480;
const int offset_oy = 60;
const int squareSize = 60;

GreenPlayer::GreenPlayer(AssetsManager& assetsManager) {
    this->initPlayer(assetsManager);
    dice.initDiceFaces(assetsManager.diceFaces(color));
 }

void GreenPlayer::initPlayer(AssetsManager& assetsManager) {
    this->color = "green";
    // adding all 4 tokens
    Token token1{this->color, assetsManager.getTokenTexture(color), assetsManager.getPositions(color)};
    // setting position for the in-house tokens
    token1.setPosition(sf::Vector2f(1 * squareSize + squareSize / 2 + offset_ox, 1 * squareSize + offset_oy));
    this->takenPositions.push_back(token1.getShapePos());
    this->tokensInHouse.push_back(token1);

    Token token2{this->color, assetsManager.getTokenTexture(color), assetsManager.getPositions(color)};
    token2.setPosition(sf::Vector2f(3 * squareSize + squareSize / 2 + offset_ox, 1 * squareSize + offset_oy));
    this->takenPositions.push_back(token2.getShapePos());
    this->tokensInHouse.push_back(token2);

    Token token3{this->color, assetsManager.getTokenTexture(color), assetsManager.getPositions(color)};
    token3.setPosition(sf::Vector2f(1 * squareSize + squareSize / 2 + offset_ox, 3 * squareSize + offset_oy));
    this->takenPositions.push_back(token3.getShapePos());
    this->tokensInHouse.push_back(token3);

    Token token4{this->color, assetsManager.getTokenTexture(color), assetsManager.getPositions(color)};
    token4.setPosition(sf::Vector2f(3 * squareSize + squareSize / 2 + offset_ox, 3 * squareSize + offset_oy));
    this->takenPositions.push_back(token4.getShapePos());
    this->tokensInHouse.push_back(token4);

    sf::RectangleShape square;
    square.setSize(sf::Vector2f(squareSize, squareSize));
    square.setFillColor(sf::Color::White);
    square.setOutlineColor(sf::Color::Green);
    square.setOutlineThickness(2.0f);
    square.setPosition(240, 180);
    this->finishTiles.push_back(square);
    square.setPosition(300, 180);
    this->finishTiles.push_back(square);
    square.setPosition(240, 240);
    this->finishTiles.push_back(square);
    square.setPosition(300, 240);
    this->finishTiles.push_back(square);
}
