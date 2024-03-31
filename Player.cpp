#include "Player.h"

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

