#include "AssetsManager.h"

AssetsManager::AssetsManager() {
    this->initTextures();
}

void AssetsManager::initTextures() {
    if(!this->redToken.loadFromFile("assets/red_token.png"))
        throw textureError("assets/red_token.png");
    if(!this->blueToken.loadFromFile("assets/blue_token.png"))
        throw textureError("assets/blue_token.png");
    if(!this->greenToken.loadFromFile("assets/green_token.png"))
        throw textureError("assets/green_token.png");
    if(!this->yellowToken.loadFromFile("assets/yellow_token.png"))
        throw textureError("assets/yellow_token.png");
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