
#ifndef OOP_ASSETSMANAGER_H
#define OOP_ASSETSMANAGER_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Audio/Sound.hpp>
#include "Exceptions.h"

class AssetsManager { // class used for all the textures, fonts, and sounds that are to be used
private:
    // textures for tokens
    sf::Texture redToken;
    sf::Texture blueToken;
    sf::Texture yellowToken;
    sf::Texture greenToken;

    // functions
    void initTextures();
public:
    // constructor
    AssetsManager();

    //functions
    sf::Texture *getRed();
    sf::Texture *getBlue();
    sf::Texture *getYellow();
    sf::Texture *getGreen();
};


#endif //OOP_ASSETSMANAGER_H