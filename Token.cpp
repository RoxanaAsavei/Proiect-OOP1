
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
                if(this->line - value == 8) {
                    value = 0;
                    this->line -= value;
                    finished = true;
                }
                else {
                    break; // trebuie sa dai fix cat iti trebuie sa intri in casa
                }
            }
        }
        else if(this->line == 8) {
            if(this->col == 9) {
                this->line--;
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
    return this->line == 8 && this->col == 7;
}
