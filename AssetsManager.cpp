
#include "AssetsManager.h"

AssetsManager::AssetsManager() {
    this->initTextures();
}

void AssetsManager::initTextures() {
    this->redToken.loadFromFile("Proiect-OOP1/tokens/red_token.png");
    this->blueToken.loadFromFile("Proiect-OOP1/tokens/blue_token.png");
    this->greenToken.loadFromFile("Proiect-OOP1/tokens/green_token.png");
    this->yellowToken.loadFromFile("Proiect-OOP1/tokens/yellow_token.png");

}

sf::Texture *AssetsManager::getRed() {
    return &this->redToken;
}

sf::Texture *AssetsManager::getBlue() {
    return &this->blueToken;
}

sf::Texture *AssetsManager::getYellow() {
    return &this->yellowToken;
}

sf::Texture *AssetsManager::getGreen() {
    return &this->greenToken;
}
