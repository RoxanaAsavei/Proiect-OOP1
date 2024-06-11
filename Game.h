#ifndef OOP_GAME_H
#define OOP_GAME_H
#include <SFML/Graphics.hpp>
#include <memory>
#include "grid1.h"
#include "Dice.h"
#include "RedPlayer.h"
#include "BluePlayer.h"
#include "GreenPlayer.h"
#include "Exceptions.h"

class Game {
private:
    // window parameters
    sf::RenderWindow *window;
    sf::VideoMode videoMode;

    // game objects
    Grid grid;
    int noPlayers;
    std::vector<std::shared_ptr<Player>> Players;
    int squareSize;

    // game logic
    bool endGame;

    // functions
    void initVariables();
    void initWindow();

    static void upper(std::string& word);
public:
    // constructor & destructor
    explicit Game(int noPlayers_);
    ~Game();

    // accessors
    bool running() const;
    bool ending() const;

    // functions
    void updatePlayer(int idx);

    void render();
    void move(int idx, int &line, int &col);

    void pollEvents();

    void playersTurn(int idx);
    void winner(std::string& playerColor);
};


#endif //OOP_GAME_H