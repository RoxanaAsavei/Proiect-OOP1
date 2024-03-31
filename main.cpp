#include <ctime>
#include <SFML/Graphics.hpp>
#include "Game.h"

/**
 * DO TO
 * - ce facem cand 2 piese ale aceluiasi jucator ajung in aceeasi celula?
 * - adaugare alti playeri
 *
 * */

int main() {
    // init srand
    std::srand(static_cast<unsigned>(time(NULL)));
    Game game;

    // game loop
    while(game.running() and !game.ending()) { // window is still open
        game.render(); // render grid & tokens & dice
        game.displayDice(); // rolling the dice
        // update
        game.update();
        // rendering the grid after the updates
        game.render();
        // take out the tokens that have finished
        game.clearGrid();

    }

    return 0;

}