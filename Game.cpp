#include "Game.h"

const int squareSize = 60;
const int offset_ox = 480;
const int offset_oy = 60;
const sf::Color bg = sf::Color{2,71,77};
const sf::Color txt = sf::Color::White;


void Game::initWindow() {
    this->videoMode = sf::VideoMode(1800, 1000);
    this->window = new sf::RenderWindow(this->videoMode, "Ludo game", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

void Game::initVariables() {
    this->endGame = false;
    this->endGame = false;
    Players.push_back(std::make_shared<RedPlayer>());
    std::vector<std::string> colors = {"blue", "green", "yellow"};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(colors.begin(), colors.end(), gen);
    for(int i = 0; i < noPlayers - 1; ++i) {
        if(colors[i] == "blue") {
            Players.push_back(std::make_shared<BluePlayer>());
        }
        else if(colors[i] == "green") {
            Players.push_back(std::make_shared<GreenPlayer>());
        }
        else {
            Players.push_back(std::make_shared<YellowPlayer>());
        }
    }
}

// constructor & destructor

Game::~Game() {
    delete this->window;
}
Game::Game() {
    state = GameState::start;
    this->initWindow();
    startGame();
}

void Game::pollEvents() {
    sf::Event ev;
    while(this->window->pollEvent(ev)) {
        if(ev.type == sf::Event::Closed) {
            this->window->close();
        }
        else if(ev.type == sf::Event::KeyPressed) {
            if(ev.key.code == sf::Keyboard::Escape)
                this->window->close();
        }
    }

}



void Game::render() { // the drawing part
    /**
     *  - clear old frame
     *  - render objects
     *  - display frame in window
     * */
    if(this->running()) {
        this->window->clear(sf::Color{163, 228, 215});
        // draw game objects
        this->grid.renderGrid(*this->window);
        for(int i = 0; i < noPlayers; ++i) {
            Players[i]->renderTokens(*this->window);
        }
        this->window->display();
    }

}

bool Game::running() const {
    return this->window->isOpen();
}


bool Game::ending() const {
    return this->endGame;
}

void Game::winner(std::string& playerColor) {
    sf::Font font;
    if(!font.loadFromFile("assets/Davis_Preview.ttf")) {
        throw fontError("assets/Davis_Preview.ttf");
    }
    sf::Text text;
    text.setFont(font);
    upper(playerColor);
    std::string mesaj = playerColor + "\nWON!";
    text.setString(mesaj);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(120);
    text.setOutlineThickness(3.f);
    text.setOutlineColor(sf::Color::Black);
    text.setPosition(5 * squareSize + offset_ox, 5 * squareSize + offset_oy);
    this->window->clear(sf::Color{163, 228, 215});
    this->window->draw(text);
    this->window->display();
    sf::sleep(sf::seconds(3));
}

void Game::upper(std::string &word) {
    for(long long unsigned int i = 0; i < word.length(); ++i)
        word[i] = toupper(word[i]);
}



void Game::playersTurn(int idx) {

    if(std::dynamic_pointer_cast<RedPlayer>(Players[idx])) {
        std::shared_ptr<RedPlayer> redPlayer = std::dynamic_pointer_cast<RedPlayer>(Players[idx]);
        this->window->clear(sf::Color{163, 228, 215});
        this->grid.renderGrid(*this->window);
        for(int i = 0; i < noPlayers; ++i) {
            Players[i]->renderTokens(*this->window);
        }
        redPlayer->displayText(*this->window);
        window->display();
        sf::sleep(sf::seconds(1));
    }
    Players[idx]->displayDice(*this->window, *this);
    sf::sleep(sf::milliseconds(500));
    this->updatePlayer(idx);
}

void Game::updatePlayer(int idx) {
    int line, col;
    this->move(idx, line, col); // mi-am mutat eu pionii
    // restul sa se duca la casa lor daca e cazul
    for(int i = 0; i < noPlayers; ++i) {
        if(i != idx) {
            Players[i]->back(line, col);
        }
    }
}

void Game::move(int idx, int &line, int &col) {
    this->pollEvents();
    if(this->running()) {
        Players[idx]->updateTokens(line, col, *this->window);
    }
    // end game condition
    if(Players[idx]->inGame() == 0 && Players[idx]->inHouse() == 0) {
        this->winner(Players[idx]->getColor());
        this->endGame = true;
    }
}





void Game::playerSelection() {
 // setam butoanele
    sf::Font font;
    if(!font.loadFromFile("assets/Ladywish.otf")) {
        throw fontError("assets/Ladywish.otf");
    }
    sf::Text mesaj;
    mesaj.setString("Select the number of players:");
    mesaj.setFont(font);
    mesaj.setCharacterSize(100);
    mesaj.setFillColor(sf::Color::White);
    mesaj.setOutlineThickness(3.f);
    mesaj.setOutlineColor(sf::Color::Black);
    mesaj.setPosition(240,120);


    std::vector<Button> butoane;
    Button btn1("2", {300, 180}, 50, bg, txt);
    btn1.setPosition({420, 300});

    butoane.emplace_back(btn1);

    Button btn2("3", {300, 180}, 50, bg, txt);
    btn2.setPosition({1020, 300});

    butoane.emplace_back(btn2);

    Button btn3("4", {300, 180}, 50, bg, txt);
    btn3.setPosition({720, 640});

    butoane.emplace_back(btn3);

    for(int i = 0; i < 3; ++i) {
        butoane[i].setFont(font);
    }

    std::string chosen;
    bool done = false;

    while(window->isOpen() and !done) {
       //  pollEvents();
        sf::Event event;
        while(window->pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window->close();
                    break;

                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape)
                        window->close();
                    break;

                case sf::Event::MouseMoved:
                    for (int i = 0; i < 3; ++i) {
                        if (butoane[i].isMouseOver(*window)) {
                            butoane[i].setBgColor(txt);
                            butoane[i].setTextColor(bg);
                        } else {
                            butoane[i].setBgColor(bg);
                            butoane[i].setTextColor(txt);
                        }
                    }
                    break;

                case sf::Event::MouseButtonPressed:
                    for (int i = 0; i < 3; ++i) {
                        if (butoane[i].isMouseOver(*window)) {
                            chosen = butoane[i].getText();
                            done = true;
                        }
                    }
                    break;

                default:
                    break;
            }

        }
        window->clear(sf::Color{163, 228, 215});
        window->draw(mesaj);
        for(int i = 0; i < 3; ++i) {
            butoane[i].drawTo(*window);
        }
        window->display();
    }

    if(done) {
        try{
            noPlayers = std::stoi(chosen);
            state = GameState::playing;
            this->initVariables();
            // face figuri la prima randare
            window->clear(sf::Color{163, 228, 215});;
            render();
            window->display();
            runGame();
        }
        catch(std::invalid_argument& error) {
            std::cout << "Nu este un numar: " << error.what() << "\n";
        }
        catch(std::out_of_range& error) {
            std::cout << "Numarul este prea mic / mare: " << error.what() << "\n";
        }
        catch(fileError& error) {
            std::cout << "Eroare de la fisiere: " << error.what() << "\n";
        }
        catch(textureError& error) {
            std::cout << "Eroare de la texturi: " << error.what() << "\n";
        }
        catch(fontError& error) {
            std::cout << "Eroare la font: " << error.what() << "\n";
        }
        catch(gameExceptions& error) {
            std::cout << "Alta eroare de la joc: " << error.what();
        }
    }

}

void Game::startGame() {
    // afisam un text si un buton de start
    sf::Text titlu;
    sf::Font font;
    if(!font.loadFromFile("assets/Davis_Preview.ttf")) {
        throw fontError("assets/Davis_Preview.ttf");
    }
    std::string content = "Play Ludo now!\n";
    titlu.setString(content);
    titlu.setFont(font);
    titlu.setCharacterSize(120);
    titlu.setFillColor(txt);
    titlu.setOutlineColor(bg);
    titlu.setOutlineThickness(5);
    titlu.setPosition(offset_ox, 3 * squareSize + offset_oy);


    Button butonStart("START", {300, 180}, 50, bg, txt);
    butonStart.setFont(font);
    butonStart.setPosition(sf::Vector2f{300 + offset_ox, 600 + offset_oy});

    bool clicked = false;

    while(window->isOpen() && !clicked) {
        // pollEvents();
        sf::Event event;
        while(window->pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window->close();
                    break;

                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape)
                        window->close();
                    break;

                case sf::Event::MouseButtonPressed:
                    if(butonStart.isMouseOver(*this->window)) {
                        clicked = true;
                        break;
                    }
                    break;

                case sf::Event::MouseMoved:
                    if(butonStart.isMouseOver(*this->window)) {
                        butonStart.setBgColor(txt);
                        butonStart.setTextColor(bg);
                    }
                    else {
                        butonStart.setBgColor(bg);
                        butonStart.setTextColor(txt);
                    }
                    break;

                default:
                    break;
            }
        }

        window->clear(sf::Color{163, 228, 215});
        window->draw(titlu);
        butonStart.drawTo(*this->window);
        window->display();

    }

    if(clicked) {
        state = GameState::playerSelection;
        playerSelection();
    }


}

void Game::runGame() {
    int turn = 0;
    while(running() and !ending()) { // window is still open
        //window->clear(sf::Color{163, 228, 215});
        render(); // render grid & tokens & dice
        playersTurn(turn);
        render();
        turn++;
        turn = turn % noPlayers;
        sf::sleep(sf::seconds(1));
    }
}

void Game::renderAddition() {
    if(this->running()) {
        // draw game objects
        this->grid.renderGrid(*this->window);
        for(int i = 0; i < noPlayers; ++i) {
            Players[i]->renderTokens(*this->window);
        }
        this->window->display();
    }
}


