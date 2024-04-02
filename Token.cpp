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
    if(this->color == "red") {
        this->shape.setTexture(assetsManager.getRed());
    }
    else if(this->color == "blue") {
        this->shape.setTexture(assetsManager.getBlue());
    }
    else if(this->color == "green") {
        this->shape.setTexture(assetsManager.getGreen());
    }
    else { // yellow
        this->shape.setTexture(assetsManager.getYellow());
    }

}

void Token::renderToken(sf::RenderWindow &window) const {
    window.draw(this->shape);
}

void Token::determinePos() { // 60 as the square size in the grid
    this->position.x = this->col * 60 + offset_ox;
    this->position.y = this->line * 60 + offset_oy;
    this->shape.setPosition(this->position.x, this->position.y);
}

bool Token::final() const {
    return this->line == 7 && this->col == 7;
}

void Token::updatePos(int addOx, int addOy) {
    // adauga la pozitia curenta cei 2 parametri
    sf::Vector2f posCurrent = this->shape.getPosition();
    posCurrent.x += addOx;
    posCurrent.y += addOy;
    this->setPosition(posCurrent);

}
