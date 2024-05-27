#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H
#include "Token.h"
#include "AssetsManager.h"
#include "Dice.h"

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
    Dice dice;

public:

    // accessors
    int inHouse() const;
    int inGame() const;
    int out() const;
    //functions
    bool canMove(int move);
    void renderTokens(sf::RenderWindow &window);
    void back(int line, int col);
    void place(Token &token, std::pair<int, int> celula);
    void resize(std::pair<int, int> celula);
    void updateFree(sf::Vector2<float> position); // & strica treaba
    void updateTaken(sf::Vector2<float> position);
    void addTokenInGame(Token& t);
    Token& getTokenInHouse(int index);
    Token& getTokenInGame(int index);
    void eraseFromInHouse(int index);
    void eraseFromInGame(int index);
    sf::Vector2 <float> outPosition();
    void takeTokenOut(Token& t);
    virtual void displayDice(sf::RenderWindow& window);
    std::string& getColor();
    virtual void updateTokens(int &line, int &col, sf::RenderWindow &window);
    int random() const;
};


#endif //OOP_PLAYER_H