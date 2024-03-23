
#include "Token.h"

void Token::setPosition(sf::Vector2f newPosition) {
    this->position = newPosition;
}

void Token::initToken() {
    this->initTexture();
    this->line = 0;
    this->col = 0;
    this->position = sf::Vector2f(0.f, 0.f);
    this->sprite.setScale(0.2f, 0.2f);
}

void Token::initTexture() {
    if(this->color == "yellow") {
        this->texture.loadFromFile("Proiect-OOP1/tokens/yellow_token.png");
    }
    else if(this->color == "blue") {
        this->texture.loadFromFile("Proiect-OOP1/tokens/blue_token.png");
    }
    else if(this->color == "green") {
        this->texture.loadFromFile("Proiect-OOP1/tokens/green_token.png");
    }
    else { // color == "red"
        this->texture.loadFromFile("Proiect-OOP1/tokens/red_token.png");
    }
}

Token::Token(const std::string &color_) : color(color_) {
    initToken();
}

void Token::renderToken(sf::RenderWindow &window) const {
    window.draw(this->sprite);
}

void Token::determinePos() { // 60 as the square size in the grid
    this->position.x = this->col * 60;
    this->position.y = this->line * 60;
}

void Token::move(int value, bool &finished) {
    int line = this->line;
    int col = this->col;
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
                if(line - value == 8) {
                    value = 0;
                    line -= value;
                    finished = true;
                }
                else {
                    break; // trebuie sa dai fix cat iti trebuie sa intri in casa
                }
            }
        }
        else if(line == 8) {
            if(col == 9) {
                line--;
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
    this->line = line;
    this->col = col;
    this->determinePos();

}

bool Token::final() const {
    return this->line == 8 && this->col == 7;
}
