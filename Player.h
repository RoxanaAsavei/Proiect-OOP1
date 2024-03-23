#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H
#include "Token.h"

class Player {
public:
    std::vector<Token> tokensInGame;
    std::vector<Token> tokensInHouse;
private:
    std::string color;


    // functions
    void initPlayer();

public:
    // constructor
    Player();

    // accessors
    int inHouse() const;
    int inGame() const;

    //functions
    void renderTokens(sf::RenderWindow &window);
};


#endif //OOP_PLAYER_H
