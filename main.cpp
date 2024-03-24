#include <ctime>
#include <SFML/Graphics.hpp>
#include "Game.h"

int main() {
    // init srand
    std::srand(static_cast<unsigned>(time(NULL)));
    Game game;


    // game loop
    while(game.running() and !game.ending()) { // window is still open
        game.render(); // render grid & tokens
        // rolling the dice
        game.displayDice();
        // update
        game.update();
        // render grid & tokens after tokens being moved
        game.render();
        // take out the tokens that have finished
        game.clearGrid();

    }
    return 0;

}