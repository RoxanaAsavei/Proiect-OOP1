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
    int turn = 0; // cand e 0 muta rosu, cand e 1 muta albastru

    // game loop
    while(game.running() and !game.ending()) { // window is still open
        game.render(); // render grid & tokens & dice
        game.update(turn);
        turn = 1 - turn;
      //  sf::sleep(sf::seconds(2));
    }

    return 0;

}