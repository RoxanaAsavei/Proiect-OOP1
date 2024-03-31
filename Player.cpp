#include "Player.h"

const int offset_ox = 480;
const int offset_oy = 60;

Player::Player() {
    initPlayer();
}

void Player::initPlayer() {
    this->color = "red";
    // adding all 4 tokens
    Token token1{this->color, this->assetsManager};
    // setting position for the in-house tokens
    token1.setPosition(sf::Vector2f(1 * 60 + 30 + offset_ox, 10 * 60 + offset_oy));
    this->tokensInHouse.push_back(token1);

    Token token2{this->color, this->assetsManager};
    token2.setPosition(sf::Vector2f(3 * 60 + 30 + offset_ox, 10 * 60 + offset_oy));
    this->tokensInHouse.push_back(token2);

    Token token3{this->color, this->assetsManager};
    token3.setPosition(sf::Vector2f(1 * 60 + 30 + offset_ox, 12 * 60 + offset_oy));
    this->tokensInHouse.push_back(token3);

    Token token4{this->color, this->assetsManager};
    token4.setPosition(sf::Vector2f(3 * 60 + 30 + offset_ox, 12 * 60 + offset_oy));
    this->tokensInHouse.push_back(token4);

}

void Player::renderTokens(sf::RenderWindow &window) {
    for(const auto& t : this->tokensInHouse) {
        t.renderToken(window);
    }
    for(const auto& t: this->tokensInGame) {
        t.renderToken(window);
    }

}

int Player::inHouse() const {
    return this->tokensInHouse.size();
}

int Player::inGame() const {
    return this->tokensInGame.size();
}

