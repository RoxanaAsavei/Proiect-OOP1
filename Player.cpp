#include "Player.h"



Player::Player() {
    initPlayer();
}

void Player::initPlayer() {
    this->color = "red";
    // adding all 4 tokens
    Token token{color};
    // setting position for the in-house tokens
    token.setPosition(sf::Vector2f(1 * 60 - 4 , 10 * 60));
    this->tokensInHouse.push_back(token);

    token.setPosition(sf::Vector2f(3 * 60 - 4 , 10 * 60));
    this->tokensInHouse.push_back(token);

    token.setPosition(sf::Vector2f(1 * 60 - 4 , 12 * 60));
    this->tokensInHouse.push_back(token);

    token.setPosition(sf::Vector2f(3 * 60 - 4 , 12 * 60));
    this->tokensInHouse.push_back(token);

}

void Player::renderTokens(sf::RenderWindow &window) {
    for(auto t : this->tokensInHouse) {
        t.renderToken(window);
    }
    for(auto t: this->tokensInGame) {
        t.renderToken(window);
    }

}

int Player::inHouse() const {
    return this->tokensInHouse.size();
}

int Player::inGame() const {
    return this->tokensInGame.size();
}

