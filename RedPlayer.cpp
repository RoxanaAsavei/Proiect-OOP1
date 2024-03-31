#include "RedPlayer.h"

const int offset_ox = 480;
const int offset_oy = 60;
const int squareSize = 60;

RedPlayer::RedPlayer() {
    this->initPlayer();
}

void RedPlayer::initPlayer() {
        this->color = "red";
        // adding all 4 tokens
        Token token1{this->color, this->assetsManager};
        // setting position for the in-house tokens
        token1.setPosition(sf::Vector2f(1 * squareSize + squareSize / 2 + offset_ox, 10 * squareSize + offset_oy));
        this->tokensInHouse.push_back(token1);

        Token token2{this->color, this->assetsManager};
        token2.setPosition(sf::Vector2f(3 * squareSize + squareSize / 2 + offset_ox, 10 * squareSize + offset_oy));
        this->tokensInHouse.push_back(token2);

        Token token3{this->color, this->assetsManager};
        token3.setPosition(sf::Vector2f(1 * squareSize + squareSize / 2 + offset_ox, 12 * squareSize + offset_oy));
        this->tokensInHouse.push_back(token3);

        Token token4{this->color, this->assetsManager};
        token4.setPosition(sf::Vector2f(3 * squareSize + squareSize / 2 + offset_ox, 12 * squareSize + offset_oy));
        this->tokensInHouse.push_back(token4);
}
