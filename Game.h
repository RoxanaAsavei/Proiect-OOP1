#ifndef OOP_GAME_H
#define OOP_GAME_H
#include <SFML/Graphics.hpp>
#include "grid1.h"
#include "Dice.h"
#include "Player.h"

class Game {
private:
    // window parameters
    sf::RenderWindow *window;
    sf::VideoMode videoMode;
    sf::Event ev;

    // mouse positions
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    // game objects
    Grid grid;
    Dice dice;
    Player player;
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
    void update();
    void updateTokens();
    void updateMousePosition();

    void render();
    void renderDice();
    void displayDice();

    void pollEvents();
    void clearGrid();

    bool clickedOn(int pos);
};


#endif //OOP_GAME_H
