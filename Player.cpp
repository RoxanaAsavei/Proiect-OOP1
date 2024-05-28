#include "Player.h"

const int squareSize = 60;
const int offset_ox = 480;
const int offset_oy = 60;
const int half = squareSize / 2;


bool Player::canMove(int move) {
    for(const auto& t: this->tokensInGame) {
        if(!t.immovable(move)) {
            return true;
        }
    }
    return false;
}

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

// playerul isi duce inapoi in casa toti pionii de la pozitia (line, col)
void Player::back(int line, int col) {
    // place back in the house the tokens in cell (line, col)
    int length = this->inGame();
    for(int i = 0; i < length; ++i) {
        if(this->tokensInGame[i].getCoord() == std::make_pair(line, col)) {
            this->tokensInGame[i].takeHome(this->freePositions[0]);
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

void Player::place(Token& token, std::pair<int, int> celula) {
    /** cand ii dau place unui token am doua optiuni:
     - in casuta (line, col) sa mai afla si alti pioni de ai lui
     - el e primul din neamul lui care ajunge aici
 */
    // vedem cati pioni de ai lui se afla aici
    int sameTile = 0;
    for(auto& t : this->tokensInGame) {
        if(this->contains(t, celula)) {
            sameTile++;
        }
    }
    if(sameTile == 0) { // e singur, are tot spatiul la dispozitie
        token.setShapeSize(sf::Vector2 <float> {squareSize, squareSize});
        token.determinePos();
    }
    else { // nu e singur, avem o problema
        // clar imparte patratul cu cineva
        token.setShapeSize(sf::Vector2 <float> {half, half});
        if(sameTile == 1) { // tb redimensionat cel existent si plasat si asta nou
            // il redimensionam pe ala existent, ca pozitie ramane la fel
            for(int i = 0; i < this->inGame(); ++i)
                if(this->contains(this->tokensInGame[i], celula)) {
                    this->tokensInGame[i].setShapeSize(sf::Vector2 <float> {half, half});
                }
            // ii setez si lui pozitia
            // il pun initial in pozitia by default
            token.determinePos();
            token.updatePos(half, half);
        }
        else if(sameTile == 2) { // el a al treilea care vine aici
            token.determinePos();
            token.updatePos(half, 0);
        }

        else if(sameTile == 3) { // el e al patrulea
            token.determinePos();
            token.updatePos(0, half);
        }
    }

}


void Player::resize(std::pair<int, int> celula) {
    // verifica daca in celula (line, col) am un singur pion ramas si atunci il face mare
    int pos = -1; // default value
    int sameTile = 0;
    for(int i = 0; i < this->inGame(); ++i) {
        if(this->contains(tokensInGame[i], celula)) {
            pos = i;
            sameTile++;
        }
    }

    if(sameTile == 1) {
        this->tokensInGame[pos].determinePos();
        this->tokensInGame[pos].setShapeSize(sf::Vector2 <float> {squareSize, squareSize});
    }
}

void Player::updateFree(sf::Vector2<float> position) {
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

void Player::updateTaken(sf::Vector2<float> position) {
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

void Player::addTokenInGame(Token &t) {
    this->tokensInGame.emplace_back(t);
}

Token &Player::getTokenInHouse(int index) {
    return this->tokensInHouse[index];
}

Token &Player::getTokenInGame(int index) {
    return this->tokensInGame[index];
}

void Player::eraseFromInHouse(int index) {
    this->tokensInHouse.erase(this->tokensInHouse.begin() + index);
}

void Player::eraseFromInGame(int index) {
    this->tokensInGame.erase(this->tokensInGame.begin() + index);
}

sf::Vector2<float> Player::outPosition() {
    return this->finishTiles[this->out()].getPosition();
}

void Player::takeTokenOut(Token &t) {
    this->tokensOut.emplace_back(t);
}

void Player::displayDice(sf::RenderWindow &window) {
    this->pollEvents(window);
    dice.renderDice(window); // afiseaza o fata a zarului cat sa o vezi
    sf::sleep(sf::milliseconds(500));
    for(int i = 0; i < 5; ++i) {
        this->pollEvents(window);
        if(!this->running(window))
            break;
        dice.Roll();
        dice.renderDice(window);
        sf::sleep(sf::milliseconds(100));
    }
}

std::string &Player::getColor() {
    return this->color;
}

void Player::updateTokens(int &line, int &col, sf::RenderWindow &window) {
    this->pollEvents(window);
    if(!this->running(window)) {
        return;
    }
    if(this->dice.getDiceValue() == 5 and this->inHouse()) { // e obligat sa scoata din casa
        Token& t = this->getTokenInHouse(0);
        t.setIndex(0);
        this->updateFree(t.getShapePos());
        this->place(t, t.getCoord());
        // place it in game
        std::pair<int, int> poz = t.getCoord();
        line = poz.first;
        col = poz.second;
        this->addTokenInGame(t);
        this->eraseFromInHouse(0);
    }

    else { // trebuie sa mute unul dintre pionii din joc
        // vad daca am unul aproape de a intra in casa
        bool moved = false;
        int diceValue = this->dice.getDiceValue();
        for(int i = 0; i < this->inGame() && !moved; ++i) {
            Token& t = this->getTokenInGame(i);
            if(t.almostDone() && !t.immovable(diceValue + 1)) {
                bool finished = false;
                t.setPrevPos();
                t.move(diceValue + 1, finished);
                moved = true;
                std::pair<int, int> poz = t.getCoord();
                line = poz.first;
                col = poz.second;
                this->place(t, t.getCoord());
                this->resize(t.getPrev());
                if(t.final()) {
                    t.setPosition(this->outPosition());
                    this->takeTokenOut(t);
                    this->eraseFromInGame(i);
                }
            }
        }

        if(!moved and this->canMove(diceValue + 1)) {
            // generez un indice random pt un token mutabil
            while(!moved) {
                int index = this->random();
                Token& t = this->getTokenInGame(index);
                if(!t.immovable(diceValue + 1)) {
                    bool finished = false;
                    t.setPrevPos();
                    t.move(diceValue + 1, finished);
                    moved = true;
                    std::pair<int, int> poz = t.getCoord();
                    line = poz.first;
                    col = poz.second;
                    if(t.final()) {
                        t.setPosition(this->outPosition());
                        this->takeTokenOut( t);
                        this->eraseFromInGame(index);
                    }
                    else {
                        this->place(t, t.getCoord());
                    }
                    this->resize(t.getPrev());
                }
            }
        }
    }
}

int Player::random() const {
    std::srand(static_cast<unsigned>(time(NULL)));
    return rand() % this->inGame();
}

void Player::pollEvents(sf::Window &window) {
    sf::Event ev;
    while(window.pollEvent(ev)) {
        if(ev.type == sf::Event::Closed) {
            window.close();
        }
        else if(ev.type == sf::Event::KeyPressed) {
            if(ev.key.code == sf::Keyboard::Escape)
                window.close();
        }
    }
}

bool Player::running(sf::Window &window) const {
    return window.isOpen();
}

bool Player::contains(const Token &token, std::pair<int, int> coord) {
    /**
   * returneaza true daca token e in celula (line, col)
   * */
    sf::Vector2f coordCel;
    coordCel.x = coord.second * squareSize + offset_ox;
    coordCel.y = coord.first * squareSize + offset_oy;
    sf::Vector2f pos = token.getShapePos();
    if(coordCel.x == pos.x && coordCel.y == pos.y) {
        return true;
    }
    if(coordCel.x + half == pos.x && coordCel.y == pos.y) {
        return true;
    }
    if(coordCel.x + half == pos.x && coordCel.y + half == pos.y) {
        return true;
    }
    if(coordCel.x == pos.x && coordCel.y + half == pos.y) {
        return true;
    }
    return false;
}

