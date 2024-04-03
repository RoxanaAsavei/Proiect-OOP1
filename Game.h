#ifndef OOP_GAME_H
#define OOP_GAME_H
#include <SFML/Graphics.hpp>
#include "grid1.h"
#include "Dice.h"
#include "RedPlayer.h"
#include "BluePlayer.h"

class Game {
private:
    // window parameters
    sf::RenderWindow *window;
    sf::VideoMode videoMode;

    // mouse positions
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    // game objects
    Grid grid;
    Dice dice;
    RedPlayer redPlayer;
    BluePlayer bluePlayer;
    int squareSize;

    // game logic
    bool endGame;

    // functions
    void initVariables();
    void initWindow();

public:
    // constructor & destructor
    Game();
    ~Game();

    // accessors
    bool running() const;
    bool ending() const;

    // functions
    void update(int turn);
    void updateRed();
    void updateTokensRed();
    void updateBlue();
    void updateTokensBlue();

    void updateMousePosition();

    void render();
    void renderDice();
    void displayDiceRed();
    void displayDiceBlue();

    void pollEvents();
    void clearGrid();

    bool clickedOn(int pos);

    void redTurn();
    void blueTurn();

    void winner(const std::string& playerColor);
};


#endif //OOP_GAME_H