#include "Game.h"
#include <ctime>
/*
 * TO DO
 * ..........
 * rand din c++
 * adaugare ceilalti playeri
 * mod 2 playeri
 * vectori de pozitie
 * timer
 * butoane
 * tricky ludo? (jump, portal, backwards etc)
 * randare patratica cu patratica la deplasare cand un pion inainteaza / este trimis inapoi in casa
 * bot smart (daca poate sa te scoata, nu ezita)
 * zar pe culori to know exactly whose turn it is
 * schimbare culori grid ca sa se vada bine pionii
 * optiune de selectat mod (1 player, 2 playeri), culoarea/culorile aferente, tipul jocului (classic, rush, ?tricky?), dificultatea lui
 * */

int main() {

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