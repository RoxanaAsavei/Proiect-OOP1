#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H
#include "Token.h"
#include "AssetsManager.h"

class Player {
public:
    std::vector<Token> tokensInGame;
    std::vector<Token> tokensInHouse;
protected:
    std::string color;
    AssetsManager assetsManager;

public:

    // accessors
    int inHouse() const;
    int inGame() const;

    //functions
    void renderTokens(sf::RenderWindow &window);
};


#endif //OOP_PLAYER_H
