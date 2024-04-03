#include "Player.h"

const int squareSize = 60;
const int offset_ox = 480;
const int offset_oy = 60;

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

void Player::back(int line, int col) {
    // place back in the house the tokens in cell (line, col)
    int length = this->inGame();
    for(int i = 0; i < length; ++i) {
        if(this->contains(this->tokensInGame[i], line, col)) {
            this->tokensInGame[i].shape.setSize(sf::Vector2f(squareSize, squareSize));
            // luam prima pozitie libera
            this->tokensInGame[i].setPosition(this->freePositions[0]);
            this->updateTaken(this->freePositions[0]);
            this->tokensInHouse.push_back(this->tokensInGame[i]);
            // nu mai e in joc
            this->tokensInGame.erase(this->tokensInGame.begin() + i);
            // sta pe loc cu forul
            i--;
            length--;

        }
    }

}

void Player::place(Token &token, int line, int col) {
    /** cand ii dau place unui token am doua optiuni:
        - in casuta (line, col) sa mai afla si alti pioni de ai lui
        - el e primul din neamul lui care ajunge aici
    */
    // vedem cati pioni de ai lui se afla aici
    int sameTile = 0;
    for(const auto& t : this->tokensInGame) {
        if(this->contains(t, line, col)) {
            sameTile++;
        }
    }
    if(sameTile == 0) { // e singur, are tot spatiul la dispozitie
        token.shape.setSize(sf::Vector2f(squareSize, squareSize));
        token.determinePos();
    }
    else { // nu e singur, avem o problema
        // clar imparte patratul cu cineva
        token.shape.setSize(sf::Vector2f(squareSize / 2, squareSize / 2));
        if(sameTile == 1) { // tb redimensionat cel existent si plasat si asta nou
            // il redimensionam pe ala existent, ca pozitie ramane la fel
            for(int i = 0; i < this->inGame(); ++i)
                if(this->contains(this->tokensInGame[i], line, col)) {
                    this->tokensInGame[i].shape.setSize(sf::Vector2f(squareSize / 2, squareSize / 2));
                }
            // ii setez si lui pozitia
            // il pun initial in pozitia by default
            token.determinePos();
            token.updatePos(squareSize / 2, squareSize / 2);
        }
        else if(sameTile == 2) { // el a al treilea care vine aici
            token.determinePos();
            token.updatePos(squareSize / 2, 0);
        }

        else if(sameTile == 3) { // el e al patrulea
            token.determinePos();
            token.updatePos(0, squareSize / 2);
        }
    }
}

bool Player::contains(const Token &token, int line, int col) {
    /**
     * returneaza true daca token e in celula (line, col)
     * */
     sf::Vector2f coordCel;
     coordCel.x = col * squareSize + offset_ox;
     coordCel.y = line * squareSize + offset_oy;
     sf::Vector2f pos = token.shape.getPosition();
     if(coordCel.x == pos.x && coordCel.y == pos.y) {
         return true;
     }
     if(coordCel.x + squareSize / 2 == pos.x && coordCel.y == pos.y) {
         return true;
     }
    if(coordCel.x + squareSize / 2 == pos.x && coordCel.y + squareSize / 2 == pos.y) {
        return true;
    }
    if(coordCel.x == pos.x && coordCel.y + squareSize / 2 == pos.y) {
        return true;
    }
    return false;
}

void Player::resize(int line, int col) {
    // verifica daca in celula (line, col) am un singur pion ramas si atunci il face mare
    int pos = -1; // default value
    int sameTile = 0;
    for(int i = 0; i < this->inGame(); ++i) {
        if(this->contains(this->tokensInGame[i], line, col)) {
            pos = i;
            sameTile++;
        }
    }

    if(sameTile == 1) {
        this->tokensInGame[pos].determinePos();
        this->tokensInGame[pos].shape.setSize(sf::Vector2f(squareSize, squareSize));
    }
}

void Player::updateFree(sf::Vector2f &position) {
    // whenever we free a position
    // the position is no longer taken
    for(unsigned long long i = 0; i < this->takenPositions.size(); ++i) {
        if(this->takenPositions[i] == position) {
            this->takenPositions.erase(this->takenPositions.begin() + int(i));
            break;
        }
    }
    // make it free
    this->freePositions.push_back(position);
}

void Player::updateTaken(sf::Vector2f &position) {
    // whenever a position is taken
    // the position is no longer free
    for(unsigned long long i = 0; i < this->freePositions.size(); ++i) {
        if(this->freePositions[i] == position) {
            this->freePositions.erase(this->freePositions.begin() + int(i));
            break;
        }
    }
    this->takenPositions.push_back(position);

}
