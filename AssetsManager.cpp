#include "AssetsManager.h"

AssetsManager::AssetsManager() {
    this->initTextures();
}

void AssetsManager::initTextures() {
    this->redToken.loadFromFile("tokens/red_token.png");
    this->blueToken.loadFromFile("tokens/blue_token.png");
    this->greenToken.loadFromFile("tokens/green_token.png");
    this->yellowToken.loadFromFile("tokens/yellow_token.png");

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
