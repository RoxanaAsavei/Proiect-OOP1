#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H
#include "Token.h"
#include "AssetsManager.h"

class Player {
public:
    std::vector<Token> tokensInGame;
    std::vector<Token> tokensInHouse;
    std::vector<Token> tokensOut;
    std::vector<sf::RectangleShape> finishTiles;
    std::vector<sf::Vector2f> freePositions;
    std::vector<sf::Vector2f> takenPositions;
protected:
    std::string color;
    AssetsManager assetsManager;

public:

    // accessors
    int inHouse() const;
    int inGame() const;
    int out() const;
    //functions
    void renderTokens(sf::RenderWindow &window);
    void back(int line, int col);
    void place(Token& token, int line, int col);
    static bool contains(const Token& token, int line, int col);
    void resize(int line, int col);
    void updateFree(sf::Vector2f& position);
    void updateTaken(sf::Vector2f& position);
};


#endif //OOP_PLAYER_H