#ifndef OOP_ASSETSMANAGER_H
#define OOP_ASSETSMANAGER_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Audio/Sound.hpp>
#include "Exceptions.h"
#include "Singleton.h"
#include <unordered_map>

class AssetsManager : public Singleton<AssetsManager> {
private:
    // textures for tokens
    std::unordered_map<std::string, sf::Texture> tokenTexture;

    // font
    sf::Font font;

    // dice faces
    std::unordered_map<std::string, std::vector<sf::Texture> > diceTextures;

    // positions
    std::unordered_map<std::string, std::vector<std::pair<int, int> > > positions;

    // functions
    void initTokenTextures();
    void initFonts();
    void initDiceTextures();
    void initDice(const std::string& color);
    void initPositions();
    void readPositions(const std::string& color);
public:
    // constructor
    AssetsManager();

    //functions
    sf::Texture* getTokenTexture(const std::string& color);
    sf::Font& getFont();
    std::vector<std::pair<int, int> >& getPositions(const std::string& color);
    std::vector<sf::Texture>& diceFaces(const std::string& color);
};


#endif //OOP_ASSETSMANAGER_H