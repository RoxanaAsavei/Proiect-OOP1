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
    this->takenPositions.push_back(token1.shape.getPosition());
    this->tokensInHouse.push_back(token1);

    Token token2{this->color, this->assetsManager};
    token2.setPosition(sf::Vector2f(3 * squareSize + squareSize / 2 + offset_ox, 10 * squareSize + offset_oy));
    this->takenPositions.push_back(token2.shape.getPosition());
    this->tokensInHouse.push_back(token2);

    Token token3{this->color, this->assetsManager};
    token3.setPosition(sf::Vector2f(1 * squareSize + squareSize / 2 + offset_ox, 12 * squareSize + offset_oy));
    this->takenPositions.push_back(token3.shape.getPosition());
    this->tokensInHouse.push_back(token3);

    Token token4{this->color, this->assetsManager};
    token4.setPosition(sf::Vector2f(3 * squareSize + squareSize / 2 + offset_ox, 12 * squareSize + offset_oy));
    this->takenPositions.push_back(token4.shape.getPosition());
    this->tokensInHouse.push_back(token4);

    sf::RectangleShape square;
    square.setSize(sf::Vector2f(squareSize, squareSize));
    square.setFillColor(sf::Color::White);
    square.setOutlineColor(sf::Color::Red);
    square.setOutlineThickness(2.0f);
    square.setPosition(240, 720);
    this->finishTiles.push_back(square);
    square.setPosition(300, 720);
    this->finishTiles.push_back(square);
    square.setPosition(240, 780);
    this->finishTiles.push_back(square);
    square.setPosition(300, 780);
    this->finishTiles.push_back(square);
}

void RedPlayer::move(Token &token, int value, bool &finished) {
    while(value and !finished) {
        if(token.col == 6) {
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
                token.line--;
            }
            else {
                if(token.line - value > 8) {
                    token.line -= value;
                    break;
                }
                else if(token.line - value == 7){
                    token.line = 7;
                    finished = true;
                    break; // trebuie sa dai fix cat iti trebuie sa intri in casa
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
        else if(token.line == 7) {
            if(token.col == 0) {
                token.line--;
            }
            else if(token.col == 14) {
                token.line++;
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
        value--;
    }
}

bool RedPlayer::immovable(const Token &token, int move) {
    return token.col == 7 && (token.line >=9 && token.line <= 13) &&
           (token.line - move < 7 || token.line - move == 8);
}

bool RedPlayer::canMove(int move) {
    for(auto& t: this->tokensInGame) {
        if(!immovable(t, move)) {
            return true;
        }
    }
    return false;
}
