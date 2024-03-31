#include "Token.h"
#include "AssetsManager.h"

const int offset_ox = 480;
const int offset_oy = 60;

void Token::setPosition(sf::Vector2f newPosition) {
    this->shape.setPosition(newPosition);
}

void Token::initToken() {
    this->line = 0;
    this->col = 0;
    this->shape.setSize(sf::Vector2f(60, 60));
}


Token::Token(const std::string &color_, AssetsManager &assetsManager) : color(color_) {
    initToken();
    this->shape.setTexture(assetsManager.getRed());
}

void Token::renderToken(sf::RenderWindow &window) const {
    window.draw(this->shape);
}

void Token::determinePos() { // 60 as the square size in the grid
    this->position.x = this->col * 60 + offset_ox;
    this->position.y = this->line * 60 + offset_oy;
    this->shape.setPosition(this->position.x, this->position.y);
}

void Token::move(int value, bool &finished) {
    while(value and !finished) {
        if(this->col == 6) {
            if(this->line == 9) {
                this->line--;
                this->col--;
            }
            else if(this->line == 0) {
                this->col++;
            }
            else {
                this->line--;
            }
        }
        else if(this->col == 8) {
            if(this->line == 5) {
                this->line++;
                this->col++;
            }
            else if(this->line == 14) {
                this->col--;
            }
            else {
                this->line++;
            }
        }
        else if(this->col == 7) {
            if(this->line == 0) {
                this->col++;
            }
            else if(this->line == 14) {
                this->line--;
            }
            else {
                if(this->line - value > 8) {
                    this->line -= value;
                    value = 0;
                    break;
                }
                else if(this->line - value == 7){
                    value = 0;
                    this->line = 7;
                    finished = true;
                    break; // trebuie sa dai fix cat iti trebuie sa intri in casa
                }
            }
        }
        else if(this->line == 8) {
            if(this->col == 9) {
                this->line++;
                this->col--;
            }
            else if(this->col == 0) {
                this->line--;
            }
            else {
                this->col--;
            }
        }
        else if(this->line == 7) {
            if(this->col == 0) {
                this->line--;
            }
            else if(this->col == 14) {
                this->line++;
            }
        }
        else if(this->line == 6) {
            if(this->col == 5) {
                this->line--;
                this->col++;
            }
            else if(this->col == 14) {
                this->line++;
            }
            else {
                this->col++;
            }
        }
        value--;
    }
    this->determinePos();

}

bool Token::final() const {
    return this->line == 7 && this->col == 7;
}

bool Token::immovable(int move) {
    return this->col == 7 && (this->line >=9 && this->line <= 13) &&
    (this->line - move < 7 || this->line - move == 8);
}
