#include <fstream>
#include "AssetsManager.h"

AssetsManager::AssetsManager() {
    this->initTokenTextures();
    this->initDiceTextures();
    this->initFonts();
    this->initPositions();
}

void AssetsManager::initTokenTextures() {
    if(!this->tokenTexture["red"].loadFromFile("assets/red_token.png"))
        throw textureError("assets/red_token.png");
    if(!this->tokenTexture["blue"].loadFromFile("assets/blue_token.png"))
        throw textureError("assets/blue_token.png");
    if(!this->tokenTexture["green"].loadFromFile("assets/green_token.png"))
        throw textureError("assets/green_token.png");
    if(!this->tokenTexture["yellow"].loadFromFile("assets/yellow_token.png"))
        throw textureError("assets/yellow_token.png");
}


void AssetsManager::initFonts() {
    if(!font.loadFromFile("assets/HoneyCrepes.ttf"))
        throw fontError("assets/HoneyCrepes.ttf");
}

void AssetsManager::initDiceTextures() {
    this->initDice("red");
    this->initDice("blue");
    this->initDice("green");
    this->initDice("yellow");
}

void AssetsManager::initDice(const std::string &color) {
    for(int i = 1; i <= 6; ++i) {
        sf::Texture diceFace;
        std::string path = "assets/" + color + std::to_string(i) + ".png";
        if(!diceFace.loadFromFile(path))
            throw textureError(path);
        diceTextures[color].emplace_back(diceFace);
    }
}

void AssetsManager::initPositions() {
    readPositions("red");
    readPositions("blue");
    readPositions("green");
    readPositions("yellow");
}

void AssetsManager::readPositions(const std::string &color) {
    std::string fileName = "read" + color + ".txt";
    std::ifstream fin(fileName);
    if(!fin.is_open()) {
        throw fileError(fileName);
    }
    std::pair <int, int> pozitie;
    while(fin >> pozitie.first >> pozitie.second)
        positions[color].emplace_back(pozitie);

}

sf::Texture* AssetsManager::getTokenTexture(const std::string &color) {
    return &tokenTexture[color];
}

sf::Font &AssetsManager::getFont() {
    return font;
}

std::vector<std::pair<int, int> > &AssetsManager::getPositions(const std::string &color) {
    return positions[color];
}

std::vector<sf::Texture> &AssetsManager::diceFaces(const std::string &color) {
    return diceTextures[color];
}

