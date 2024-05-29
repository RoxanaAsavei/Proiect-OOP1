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
 * 6 activeaza dubla 
 * */



#include "Button.h"

int main() {

    sf::RenderWindow window;
    window.create(sf::VideoMode(1800, 1000), "Ludo game", sf::Style::Titlebar | sf::Style::Close);
    sf::Font font;
    font.loadFromFile("assets/Ladywish.otf");
    sf::Text mesaj;
    mesaj.setString("Select the number of players:");
    mesaj.setFont(font);
    mesaj.setCharacterSize(100);
    mesaj.setFillColor(sf::Color::White);
    mesaj.setOutlineThickness(3.f);
    mesaj.setOutlineColor(sf::Color::Black);
    mesaj.setPosition(240,120);


    sf::Color bg = sf::Color{2,71,77};
    sf::Color txt = sf::Color::White;
    std::vector<Button> butoane;
    Button btn1("2", {300, 200}, 120, bg, txt);
    btn1.setPosition({420, 300});

    butoane.emplace_back(btn1);

    Button btn2("3", {300, 200}, 120, bg, txt);
    btn2.setPosition({1020, 300});

    butoane.emplace_back(btn2);

    Button btn3("4", {300, 200}, 120, bg, txt);
    btn3.setPosition({720, 640});

    butoane.emplace_back(btn3);

    for(int i = 0; i < 3; ++i) {
        butoane[i].setFont(font);
    }

    std::string chosen;

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Escape)
                        window.close();
                case sf::Event::MouseMoved:
                    for(int i = 0; i < 3; ++i) {
                        if(butoane[i].isMouseOver(window)) {
                            butoane[i].setBgColor(txt);
                            butoane[i].setTextColor(bg);
                        }
                        else {
                            butoane[i].setBgColor(bg);
                            butoane[i].setTextColor(txt);
                        }
                    }
                    break;
                case sf::Event::MouseButtonPressed:
                    for(int i = 0; i < 3; ++i) {
                        if(butoane[i].isMouseOver(window)) {
                            chosen = butoane[i].getText();
                            window.close();
                            break;
                        }
                    }

            }
        }
        window.clear(sf::Color{163, 228, 215});
        window.draw(mesaj);
        for(int i = 0; i < 3; ++i) {
            butoane[i].drawTo(window);
        }
        window.display();
    }

    int noPlayers = std::stoi(chosen);
    Game game(noPlayers);
    int turn = 0;

    // game loop
    while(game.running() and !game.ending()) { // window is still open
        game.render(); // render grid & tokens & dice
        sf::sleep(sf::seconds(1));
        game.playersTurn(turn);
        game.render();
        turn++;
        turn = turn % noPlayers;

    }

    return 0;
}