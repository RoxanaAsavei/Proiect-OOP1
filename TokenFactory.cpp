
#include "TokenFactory.h"

Token TokenFactory::redToken() {
    return Token("red", AssetsManager::getInstance().getTokenTexture("red"), AssetsManager::getInstance().getPositions("red"));
}

Token TokenFactory::blueToken() {
    return  Token("blue", AssetsManager::getInstance().getTokenTexture("blue"), AssetsManager::getInstance().getPositions("blue"));
}

Token TokenFactory::yellowToken() {
    return Token("yellow", AssetsManager::getInstance().getTokenTexture("yellow"), AssetsManager::getInstance().getPositions("yellow"));
}

Token TokenFactory::greenToken() {
    return Token("green", AssetsManager::getInstance().getTokenTexture("green"), AssetsManager::getInstance().getPositions("green"));
}
