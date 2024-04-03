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
    this->takenPositions.push_back(token1.shape.getPosition());

    Token token2{this->color, this->assetsManager};
    token2.setPosition(sf::Vector2f(12 * squareSize  + squareSize / 2 + offset_ox, 10 * squareSize  + offset_oy));
    this->tokensInHouse.push_back(token2);
    this->takenPositions.push_back(token2.shape.getPosition());

    Token token3{this->color, this->assetsManager};
    token3.setPosition(sf::Vector2f(10 * squareSize + squareSize / 2 + offset_ox, 12 * squareSize + offset_oy));
    this->tokensInHouse.push_back(token3);
    this->takenPositions.push_back(token3.shape.getPosition());

    Token token4{this->color, this->assetsManager};
    token4.setPosition(sf::Vector2f(12 * squareSize + squareSize / 2 + offset_ox, 12 * squareSize + offset_oy));
    this->tokensInHouse.push_back(token4);
    this->takenPositions.push_back(token4.shape.getPosition());

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
}

void BluePlayer::move(Token &token, int value, bool &finished) {
    while(value and !finished) {
        if(token.line == 7) {
            if(token.col == 0) {
                token.line--;
            }
            else if(token.col == 14) {
                token.col--;
            }
            else {
                if(token.col - value > 8) {
                    token.col -= value;
                    value = 0;
                    break;
                }

                else if(token.col - value == 7) {
                    token.col = 7;
                    value = 0;
                    finished = true;
                    break;
                }
            }
        }
        else if(token.line == 8) {
            if(token.col == 9) {
                token.line++;
                token.col--;
            }
            else if(token.col == 0) {
                token.line--;
            }
            else {
                token.col--;
            }
        }
        else if(token.line == 6) {
            if(token.col == 5) {
                token.line--;
                token.col++;
            }
            else if(token.col == 14) {
                token.line++;
            }
            else {
                token.col++;
            }
        }

        else if(token.col == 6) {
            if(token.line == 9) {
                token.line--;
                token.col--;
            }
            else if(token.line == 0) {
                token.col++;
            }
            else {
                token.line--;
            }
        }
        else if(token.col == 8) {
            if(token.line == 5) {
                token.line++;
                token.col++;
            }
            else if(token.line == 14) {
                token.col--;
            }
            else {
                token.line++;
            }
        }
        else if(token.col == 7) {
            if(token.line == 0) {
                token.col++;
            }
            else if(token.line == 14) {
                token.col--;
            }
        }
        value--;
    }

}

bool BluePlayer::immovable(Token &token, int move) {
    return token.line == 7 && (token.col >= 9 && token.col <= 13) &&
           (token.col - move == 8 || token.col - move < 7);
}

bool BluePlayer::almostDone(Token &token) {
    return token.line == 7 && token.col >= 9 && token.col <= 13;
}

int BluePlayer::random() {
    std::srand(static_cast<unsigned>(time(NULL)));
    return rand() % this->inGame();
}

bool BluePlayer::canMove(int move) {
    for(auto& t : this->tokensInGame) {
        if(!immovable(t, move)) {
            return true;
        }
    }
    return false;
}
