#include <ctime>
#include <SFML/Graphics.hpp>
#include "Game.h"

/**
 * DO TO
 * - ce facem cand 2 piese ale aceluiasi jucator ajung in aceeasi celula?
 * - full screen
 * - adaugare alti playeri
 *
 * Oprire program:
 *      - iau codul din pollevents si il pun in update
 *      - verific daca eventul a fost close window
 *      - dau break in while
 *      - restul functiilor le apelez doar daca fereastra e deschisa
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