#include "Player.h"

void Player::renderTokens(sf::RenderWindow &window) {
    for(const auto& t : this->tokensInHouse) {
        t.renderToken(window);
    }
    for(const auto& t: this->tokensInGame) {
        t.renderToken(window);
    }
    for(const auto& tile : this->finishTiles) {
        window.draw(tile);
    }
    for(const auto& t : this->tokensOut) {
        t.renderToken(window);
    }

}

int Player::inHouse() const {
    return this->tokensInHouse.size();
}

int Player::inGame() const {
    return this->tokensInGame.size();
}

int Player::out() const {
    return this->tokensOut.size();
}
