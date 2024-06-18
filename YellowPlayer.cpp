#include "YellowPlayer.h"

const int offset_ox = 480;
const int offset_oy = 60;
const int squareSize = 60;

YellowPlayer::YellowPlayer(AssetsManager& assetsManager) {
    this->initPlayer();
    dice.initDiceFaces(assetsManager.diceFaces(color));
}

void YellowPlayer::initPlayer() {
    this->color = "yellow";
    Token token1 = TokenFactory::yellowToken();
    // setting position for the in-house tokens
    token1.setPosition(sf::Vector2f(10* squareSize + squareSize / 2 + offset_ox, 1 * squareSize + offset_oy));
    this->takenPositions.push_back(token1.getShapePos());
    this->tokensInHouse.push_back(token1);

    Token token2 = TokenFactory::yellowToken();
    token2.setPosition(sf::Vector2f(12 * squareSize + squareSize / 2 + offset_ox, 1 * squareSize + offset_oy));
    this->takenPositions.push_back(token2.getShapePos());
    this->tokensInHouse.push_back(token2);

    Token token3 = TokenFactory::yellowToken();
    token3.setPosition(sf::Vector2f(10 * squareSize + squareSize / 2 + offset_ox, 3 * squareSize + offset_oy));
    this->takenPositions.push_back(token3.getShapePos());
    this->tokensInHouse.push_back(token3);

    Token token4 = TokenFactory::yellowToken();
    token4.setPosition(sf::Vector2f(12 * squareSize + squareSize / 2 + offset_ox, 3 * squareSize + offset_oy));
    this->takenPositions.push_back(token4.getShapePos());
    this->tokensInHouse.push_back(token4);

    sf::RectangleShape square;
    square.setSize(sf::Vector2f(squareSize, squareSize));
    square.setFillColor(sf::Color::White);
    square.setOutlineColor(sf::Color::Yellow);
    square.setOutlineThickness(2.0f);
    square.setPosition(1500, 180);
    this->finishTiles.push_back(square);
    square.setPosition(1560, 180);
    this->finishTiles.push_back(square);
    square.setPosition(1500, 240);
    this->finishTiles.push_back(square);
    square.setPosition(1560, 240);
    this->finishTiles.push_back(square);

}
