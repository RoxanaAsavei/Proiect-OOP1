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
    this->takenPositions.push_back(token1.getShapePos());

    Token token2{this->color, this->assetsManager};
    token2.setPosition(sf::Vector2f(12 * squareSize  + squareSize / 2 + offset_ox, 10 * squareSize  + offset_oy));
    this->tokensInHouse.push_back(token2);
    this->takenPositions.push_back(token2.getShapePos());

    Token token3{this->color, this->assetsManager};
    token3.setPosition(sf::Vector2f(10 * squareSize + squareSize / 2 + offset_ox, 12 * squareSize + offset_oy));
    this->tokensInHouse.push_back(token3);
    this->takenPositions.push_back(token3.getShapePos());

    Token token4{this->color, this->assetsManager};
    token4.setPosition(sf::Vector2f(12 * squareSize + squareSize / 2 + offset_ox, 12 * squareSize + offset_oy));
    this->tokensInHouse.push_back(token4);
    this->takenPositions.push_back(token4.getShapePos());

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
    int line = token.getLine();
    int col = token.getCol();
    while(value and !finished) {
        if(line == 7) {
            if(col == 0) {
                line--;
            }
            else if(col == 14) {
                 col--;
            }
            else {
                if(col - value > 8) {
                    col -= value;
                    break;
                }

                else if(col - value == 7) {
                    col = 7;
                    finished = true;
                    break;
                }
            }
        }
        else if(line == 8) {
            if(col == 9) {
                line++;
                col--;
            }
            else if(col == 0) {
                line--;
            }
            else {
                col--;
            }
        }
        else if(line == 6) {
            if(col == 5) {
                line--;
                col++;
            }
            else if(col == 14) {
                line++;
            }
            else {
                col++;
            }
        }

        else if(col == 6) {
            if(line == 9) {
                line--;
                col--;
            }
            else if(line == 0) {
                col++;
            }
            else {
                line--;
            }
        }
        else if(col == 8) {
            if(line == 5) {
                line++;
                col++;
            }
            else if(line == 14) {
                col--;
            }
            else {
                line++;
            }
        }
        else if(col == 7) {
            if(line == 0) {
                col++;
            }
            else if(line == 14) {
                col--;
            }
        }
        value--;
    }
    token.setLine(line);
    token.setCol(col);
}

bool BluePlayer::immovable(const Token &token, int move) {
    int line = token.getLine();
    int col = token.getCol();
    return line == 7 && (col >= 9 && col <= 13) &&
           (col - move == 8 || col - move < 7);
}

bool BluePlayer::almostDone(const Token &token) {
    int line = token.getLine();
    int col = token.getCol();
    return line == 7 && col >= 9 && col <= 13;
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
