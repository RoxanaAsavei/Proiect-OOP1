#include "AssetsManager.h"

AssetsManager::AssetsManager() {
    this->initTextures();
}

void AssetsManager::initTextures() {
    this->redToken.loadFromFile("assets/red_token.png");
    this->blueToken.loadFromFile("assets/blue_token.png");
    this->greenToken.loadFromFile("assets/green_token.png");
    this->yellowToken.loadFromFile("assets/yellow_token.png");

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