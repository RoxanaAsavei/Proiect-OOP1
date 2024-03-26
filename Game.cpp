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
    if(this->player.inGame() == 0 && this->player.inHouse() == 0) {
        this->endGame = true;
    }

}

void Game::updateTokens() {

    // daca da 6 si mai are in casa, e obligat sa scoata din casa
    if(this->dice.diceValue == 5 and this->player.inHouse()) {
        bool clickedUpon = false;
        while(!clickedUpon) {
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                this->updateMousePosition(); // iau pozitia curenta
                bool moved = false;
                for(int i = 0; i < this->player.inHouse() and !moved; ++i) {
                    this->pollEvents(); // so i can close the window at any moment
                    if(this->player.tokensInHouse[i].shape.getGlobalBounds().contains(this->mousePosView)) {
                        moved = true;
                        clickedUpon = true;
                        // get it out of house
                        this->player.tokensInHouse[i].line = 13;
                        this->player.tokensInHouse[i].col = 6;
                        this->player.tokensInHouse[i].determinePos();
                        // place it in game
                        this->player.tokensInGame.push_back(player.tokensInHouse[i]);
                        // token no longer in house
                        this->player.tokensInHouse.erase(this->player.tokensInHouse.begin() + i);
                    }

                }
            }
        }

    }

    else {
        if(this->player.inGame()) { // if the player still has tokens in game
            bool clickedUpon = false;
            while(!clickedUpon) {
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    this->updateMousePosition();
                    bool moved = false;
                    for(int i = 0; i < this->player.inGame() && !moved; ++i) {
                        this->pollEvents(); // so i can close the window at any moment
                        if(this->player.tokensInGame[i].shape.getGlobalBounds().contains(this->mousePosView)) {
                            moved = true;
                            clickedUpon = true;
                            bool finished = false;
                            this->player.tokensInGame[i].move(this->dice.diceValue + 1, finished);
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
    this->window->clear(sf::Color::White);
    // draw game objects
    this->grid.renderGrid(*this->window);
    this->player.renderTokens(*this->window);
    this->window->display();

}

bool Game::running() const {
    return this->window->isOpen();
}

bool Game::ending() const {
    return this->endGame;
}

void Game::renderDice() { // gridul si pionii deja sunt

        this->dice.Roll();
        this->dice.renderDice(*this->window);
        this->window->display();
}

void Game::clearGrid() {
        for(int i = this->player.tokensInGame.size() - 1; i >= 0; --i) {
            if(this->player.tokensInGame[i].final()) {
                this->player.tokensInGame.erase(this->player.tokensInGame.begin() + i);
            }
        }

}

void Game::displayDice() {
        this->renderDice(); // rendering the dice once
        // you have to click on it
        sf::RectangleShape diceFace = dice.getDiceFace();
        bool clickedUpon = false;
        while(!clickedUpon) {
            this->pollEvents();
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                this->updateMousePosition();
                if(diceFace.getGlobalBounds().contains(this->mousePosView)) {
                    clickedUpon = true;
                    // rolling the dice for 5 times
                    for(int i = 0; i < 5; ++i) {
                        this->renderDice();
                    }
                }
            }
        }
}






