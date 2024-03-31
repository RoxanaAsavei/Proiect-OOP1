#include "Game.h"


void Game::initWindow() {
    this->videoMode = sf::VideoMode::getDesktopMode();
    this->window = new sf::RenderWindow(this->videoMode, "Ludo game", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(6);
}

void Game::initVariables() {
    this->window = nullptr;
    this->squareSize = 60;
    this->endGame = false;
}

// constructor & destructor
Game::Game() {
    this->initVariables();
    this->initWindow();
}

Game::~Game() {
    delete this->window;
}

void Game::pollEvents() {
    while(this->window->pollEvent(this->ev)) {
        if(this->ev.type == sf::Event::Closed) {
            this->window->close();
        }
        else if(this->ev.type == sf::Event::KeyPressed) {
            if(this->ev.key.code == sf::Keyboard::Escape)
                this->window->close();
        }
    }

}

void Game::update() { // the logic behind the game
    this->pollEvents();
    if(this->running()) {
        this->updateTokens();
    }

    // end game condition
    if(this->redPlayer.inGame() == 0 && this->redPlayer.inHouse() == 0) {
        this->endGame = true;
    }

}

void Game::updateTokens() {

    // daca da 6 si mai are in casa, e obligat sa scoata din casa
    if(this->dice.diceValue == 5 and this->redPlayer.inHouse()) {
        bool clickedUpon = false;
        while(!clickedUpon && this->running()) {
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                this->updateMousePosition(); // iau pozitia curenta
                bool moved = false;
                for(int i = 0; i < this->redPlayer.inHouse() and !moved; ++i) {
                    this->pollEvents(); // so i can close the window at any moment
                    if(this->ev.type == sf::Event::Closed) {
                        break;
                    }
                    if(this->redPlayer.tokensInHouse[i].shape.getGlobalBounds().contains(this->mousePosView)) {
                        moved = true;
                        clickedUpon = true;
                        // get it out of house
                        this->redPlayer.tokensInHouse[i].line = 13;
                        this->redPlayer.tokensInHouse[i].col = 6;
                        this->redPlayer.tokensInHouse[i].determinePos();
                        // place it in game
                        this->redPlayer.tokensInGame.push_back(redPlayer.tokensInHouse[i]);
                        // token no longer in house
                        this->redPlayer.tokensInHouse.erase(this->redPlayer.tokensInHouse.begin() + i);
                    }

                }
            }
        }

    }

    else {
        if(this->redPlayer.inGame()) { // if the redPlayer still has tokens in game
            bool clickedUpon = false;
            while(!clickedUpon && this->running()) {
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    this->updateMousePosition();
                    bool moved = false;
                    for(int i = 0; i < this->redPlayer.inGame() && !moved; ++i) {
                        this->pollEvents(); // so i can close the window at any moment
                        if(this->ev.type == sf::Event::Closed) {
                            break;
                        }
                        if(clickedOn(i) && !this->redPlayer.tokensInGame[i].immovable(this->dice.diceValue + 1)) {
                            moved = true;
                            clickedUpon = true;
                            bool finished = false;
                            this->redPlayer.tokensInGame[i].move(this->dice.diceValue + 1, finished);
                        }
                    }
                }
            }
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
         this->redPlayer.renderTokens(*this->window);
         this->bluePlayer.renderTokens(*this->window);
         this->dice.renderDice(*this->window);
         this->window->display();
     }

}

bool Game::running() const {
    return this->window->isOpen();
}

bool Game::ending() const {
    return this->endGame;
}

void Game::renderDice() { // gridul si pionii deja sunt
        if(this->running()) {
            this->dice.Roll();
            this->dice.renderDice(*this->window);
            this->window->display();
        }
}

void Game::clearGrid() {
        if(this->running()) {
            for(int i = this->redPlayer.tokensInGame.size() - 1; i >= 0; --i) {
                if(this->redPlayer.tokensInGame[i].final()) {
                    this->redPlayer.tokensInGame.erase(this->redPlayer.tokensInGame.begin() + i);
                }
            }
        }
}

void Game::displayDice() {
        // you have to click on it
        sf::RectangleShape diceFace = dice.getDiceFace();
        bool clickedUpon = false;
        while(!clickedUpon && this->running()) {
            this->pollEvents();
            if(this->ev.type == sf::Event::Closed) {
                break;
            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                this->updateMousePosition();
                if(diceFace.getGlobalBounds().contains(this->mousePosView)) {
                    clickedUpon = true;
                    // rolling the dice for 5 times
                    for(int i = 0; i < 5; ++i) {
                        this->pollEvents();
                        if(this->ev.type == sf::Event::Closed) {
                            break;
                        }
                        this->renderDice();
                    }
                }
            }
        }
}

bool Game::clickedOn(int pos) {
    return this->redPlayer.tokensInGame[pos].shape.getGlobalBounds().contains(this->mousePosView);
}






