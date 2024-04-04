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
    this->takenPositions.push_back(token1.getShapePos());
    this->tokensInHouse.push_back(token1);

    Token token2{this->color, this->assetsManager};
    token2.setPosition(sf::Vector2f(3 * squareSize + squareSize / 2 + offset_ox, 10 * squareSize + offset_oy));
    this->takenPositions.push_back(token2.getShapePos());
    this->tokensInHouse.push_back(token2);

    Token token3{this->color, this->assetsManager};
    token3.setPosition(sf::Vector2f(1 * squareSize + squareSize / 2 + offset_ox, 12 * squareSize + offset_oy));
    this->takenPositions.push_back(token3.getShapePos());
    this->tokensInHouse.push_back(token3);

    Token token4{this->color, this->assetsManager};
    token4.setPosition(sf::Vector2f(3 * squareSize + squareSize / 2 + offset_ox, 12 * squareSize + offset_oy));
    this->takenPositions.push_back(token4.getShapePos());
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
    int line = token.getLine();
    int col = token.getCol();
    while(value and !finished) {
        if(col == 6) {
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
                line--;
            }
            else {
                if(line - value > 8) {
                    line -= value;
                    break;
                }
                else if(line - value == 7){
                    line = 7;
                    finished = true;
                    break; // trebuie sa dai fix cat iti trebuie sa intri in casa
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
        else if(line == 7) {
            if(col == 0) {
                line--;
            }
            else if(col == 14) {
                line++;
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
        value--;
    }
    token.setLine(line);
    token.setCol(col);
}

bool RedPlayer::immovable(const Token &token, int move) {
    int line = token.getLine();
    int col = token.getCol();
    return col == 7 && (line >=9 && line <= 13) &&
           (line - move < 7 || line - move == 8);
}

bool RedPlayer::canMove(int move) {
    for(auto& t: this->tokensInGame) {
        if(!immovable(t, move)) {
            return true;
        }
    }
    return false;
}
