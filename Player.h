#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H
#include "Token.h"
#include "AssetsManager.h"

class Player {
protected:
    std::vector<Token> tokensInGame;
    std::vector<Token> tokensInHouse;
    std::vector<Token> tokensOut;
    std::vector<sf::RectangleShape> finishTiles;
    std::vector<sf::Vector2 <float> > freePositions;
    std::vector<sf::Vector2 <float> > takenPositions;
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
    void place(Token &token, int line, int col);
    static bool contains(const Token &token, int line, int col);
    void resize(int line, int col);
    void updateFree(sf::Vector2<float> position); // & strica treaba
    void updateTaken(sf::Vector2<float> position);
    void addTokenInGame(Token& t);
    Token& getTokenInHouse(int index);
    Token& getTokenInGame(int index);
    void eraseFromInHouse(int index);
    void eraseFromInGame(int index);
    sf::Vector2 <float> outPosition();
    void takeTokenOut(Token& t);
};


#endif //OOP_PLAYER_H