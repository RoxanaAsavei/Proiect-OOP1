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
#include "YellowPlayer.h"
#include "Button.h"
#include "Singleton.h"
#include "AssetsManager.h"

enum class GameState{
    start,
    playerSelection,
    playing
};

class Game : public Singleton<Game> {
private:
    // game state
    GameState state;

    // window parameters
    sf::RenderWindow *window;
    sf::VideoMode videoMode;

    // resources
    AssetsManager &assetsManager;

    // game objects
    Grid grid;
    int noPlayers;
    std::vector<std::shared_ptr<Player>> Players;

    // game logic
    bool endGame;

    // functions
    void initVariables();
    void initWindow();

    static void upper(std::string& word);
protected:
    Game();
public:
    ~Game();

    // accessors
    bool running() const;
    bool ending() const;

    // functions
    void updatePlayer(int idx);

    void render();
    void renderAddition();
    void move(int idx, int &line, int &col);

    void pollEvents();

    void playersTurn(int idx);
    void winner(std::string& playerColor);

    void playerSelection();
    void startGame();
    void runGame();

};


#endif //OOP_GAME_H