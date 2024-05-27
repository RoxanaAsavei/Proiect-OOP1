#include "Game.h"
#include "GreenPlayer.h"

const int offset_ox = 480;
const int offset_oy = 60;

void Game::initWindow() {
    this->videoMode = sf::VideoMode(1800, 1000);
    this->window = new sf::RenderWindow(this->videoMode, "Ludo game", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

void Game::initVariables() {
    this->window = nullptr;
    this->squareSize = 60;
    this->endGame = false;
    Players.push_back(std::make_shared<RedPlayer>());
    std::vector<std::string> colors = {"blue", "green"};
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
    }
}

// constructor & destructor
Game::Game(int noPlayers_) : noPlayers(noPlayers_) {
    this->initVariables();
    this->initWindow();
}

Game::~Game() {
    delete this->window;
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


void Game::updateMousePosition() {
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
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
    font.loadFromFile("assets/Davis_Preview.ttf");
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
    for(int i = 0; i < word.length(); ++i)
        word[i] = toupper(word[i]);
}

void Game::playersTurn(int idx) {
    Players[idx]->displayDice(*this->window);
    sf::sleep(sf::seconds(1));
    this->updatePlayer(idx);
}

void Game::updatePlayer(int idx) {
    int line, col;
    this->move(idx, line, col); // mi-am mutat eu pionii
    // restul sa se duca la casa lor daca e cazul
        for(int i = 0; i < noPlayers; ++i) {
            if(i != idx) {
                Players[idx]->back(line, col);
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


