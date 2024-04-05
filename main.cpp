#include <ctime>
#include <SFML/Graphics.hpp>
#include "Game.h"

int main() {
    // init srand
    std::srand(static_cast<unsigned>(time(NULL)));
    Game game;
    int turn = 0; // 0 -> red's turn, 1 -> blue's turn

    // game loop
    while(game.running() and !game.ending()) { // window is still open
        game.render(); // render grid & tokens & dice
        game.update(turn);
        turn = 1 - turn;
    }

    return 0;

}