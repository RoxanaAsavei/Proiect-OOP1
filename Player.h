#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H

#include <iostream>
#include <memory>
#include "Token.h"
#include "Dice.h"
#include "TokenFactory.h"

class Player {
protected:
    std::vector<Token> tokensInGame;
    std::vector<Token> tokensInHouse;
    std::vector<Token> tokensOut;
    std::vector<sf::RectangleShape> finishTiles;
    std::vector<sf::Vector2 <float> > freePositions;
    std::vector<sf::Vector2 <float> > takenPositions;
    std::string color;
    Dice dice;

public:
    // destructor
    virtual ~Player() {
        std::cout << "Destructor player\n";
    }

    // accessors
    int inHouse() const;
    int inGame() const;
    int out() const;
    std::string& getColor();
    sf::Vector2 <float> outPosition();
    //functions
    void updateFree(sf::Vector2<float> position); // & strica treaba
    void updateTaken(sf::Vector2<float> position);
    bool canMove(int move);
    void renderTokens(sf::RenderWindow &window);
    void back(int line, int col);
    void place(Token &token, std::pair<int, int> celula);
    void resize(std::pair<int, int> celula);
    virtual void displayDice(sf::RenderWindow& window, class Game& game);
    virtual void updateTokens(int &line, int &col, sf::RenderWindow &window, class Game&);
    int random() const;
    void pollEvents(sf::Window &window);
    bool running(sf::Window &window) const;
    static bool contains(const Token& token, std::pair<int, int> coord);

};


#endif //OOP_PLAYER_H