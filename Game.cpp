#include "Game.h"


void Game::initWindow() {
    this->videoMode = sf::VideoMode::getDesktopMode();
    this->window = new sf::RenderWindow(this->videoMode, "Ludo game", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
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

void Game::updateRed() { // the logic behind the game
    this->pollEvents();
    if(this->running()) {
        this->updateTokensRed();
    }

    // end game condition
    if(this->redPlayer.inGame() == 0 && this->redPlayer.inHouse() == 0) {
        this->endGame = true;
    }

}

void Game::updateTokensRed() {

    // daca da 6 si mai are in casa, e obligat sa scoata din casa
    if(this->dice.diceValue == 5 and this->redPlayer.inHouse()) {
        bool clickedUpon = false;
        while(!clickedUpon && this->running()) {
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                this->updateMousePosition(); // iau pozitia curenta
                bool moved = false;
                for(int i = 0; i < this->redPlayer.inHouse() and !moved; ++i) {
                    this->pollEvents(); // so i can close the window at any moment
                    if(!this->running()) {
                        break;
                    }
                    if(this->redPlayer.tokensInHouse[i].shape.getGlobalBounds().contains(this->mousePosView)) {
                        moved = true;
                        clickedUpon = true;
                        // get it out of house
                        this->redPlayer.tokensInHouse[i].line = 13;
                        this->redPlayer.tokensInHouse[i].col = 6;
                    //    this->redPlayer.tokensInHouse[i].determinePos();
                        this->bluePlayer.back(this->redPlayer.tokensInHouse[i].line, this->redPlayer.tokensInHouse[i].col);
                        this->redPlayer.place(this->redPlayer.tokensInHouse[i], this->redPlayer.tokensInHouse[i].line, this->redPlayer.tokensInHouse[i].col);
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
        if(this->redPlayer.inGame() and this->redPlayer.canMove(this->dice.diceValue + 1)) { // if the redPlayer still has tokens in game
            bool clickedUpon = false;
            while(!clickedUpon && this->running()) {
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    this->updateMousePosition();
                    bool moved = false;
                    for(int i = 0; i < this->redPlayer.inGame() && !moved; ++i) {
                        this->pollEvents(); // so i can close the window at any moment
                        if(!this->running()) {
                            break;
                        }
                        if(clickedOn(i) && !this->redPlayer.immovable(this->redPlayer.tokensInGame[i], this->dice.diceValue + 1)) {
                            moved = true;
                            clickedUpon = true;
                            bool finished = false;
                            this->redPlayer.move(this->redPlayer.tokensInGame[i],this->dice.diceValue + 1, finished);
                            this->bluePlayer.back(this->redPlayer.tokensInGame[i].line, this->redPlayer.tokensInGame[i].col);
                            this->redPlayer.place(this->redPlayer.tokensInGame[i], this->redPlayer.tokensInGame[i].line, this->redPlayer.tokensInGame[i].col);
                            if(this->redPlayer.tokensInGame[i].final()) {
                                this->redPlayer.tokensInGame[i].setPosition(this->redPlayer.finishTiles[this->redPlayer.out()].getPosition());
                                this->redPlayer.tokensOut.push_back( this->redPlayer.tokensInGame[i]);
                                this->redPlayer.tokensInGame.erase(this->redPlayer.tokensInGame.begin() + i);
                            }
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
        this->render();
    }
}

void Game::displayDiceBlue() {
    // rolling the dice for 5 times
    for(int i = 0; i < 5; ++i) {
        this->pollEvents();
        if (!this->running()) {
            break;
        }
        this->renderDice();
    }
}

void Game::displayDiceRed() {
    // you have to click on it
    sf::RectangleShape diceFace = dice.getDiceFace();
    bool clickedUpon = false;
    while(!clickedUpon && this->running()) {
        this->pollEvents();
        if(!this->running()) {
            break;
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            this->updateMousePosition();
            if(diceFace.getGlobalBounds().contains(this->mousePosView)) {
                clickedUpon = true;
                // rolling the dice for 5 times
                for(int i = 0; i < 5; ++i) {
                    this->pollEvents();
                    if(!this->running()) {
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

void Game::redTurn() {
    this->displayDiceRed();
    sf::sleep(sf::seconds(1));
    this->updateRed();
}

void Game::blueTurn() {
    this->displayDiceBlue();
    sf::sleep((sf::seconds(1)));
    this->updateBlue();
}

void Game::updateBlue() {
    this->pollEvents();
    if(this->running()) {
        this->updateTokensBlue();
    }

    // end game condition
    if(this->bluePlayer.inGame() == 0 && this->bluePlayer.inHouse() == 0) {
        this->endGame = true;
    }
}

void Game::updateTokensBlue() {
    if(this->dice.diceValue == 5 and this->bluePlayer.inHouse()) { // e obligat sa scoata din casa
        this->bluePlayer.tokensInHouse[0].line = 8;
        this->bluePlayer.tokensInHouse[0].col = 13;
//        this->bluePlayer.tokensInHouse[0].determinePos();
        this->redPlayer.back(this->bluePlayer.tokensInHouse[0].line, this->bluePlayer.tokensInHouse[0].col);
        this->bluePlayer.place(this->bluePlayer.tokensInHouse[0], this->bluePlayer.tokensInHouse[0].line, this->bluePlayer.tokensInHouse[0].col);
        // place it in game
        this->bluePlayer.tokensInGame.push_back(this->bluePlayer.tokensInHouse[0]);
        this->bluePlayer.tokensInHouse.erase(this->bluePlayer.tokensInHouse.begin());
    }

    else { // trebuie sa mute unul dintre pionii din joc
        // vad daca am unul aproape de a intra in casa
        bool moved = false;
        for(int i = 0; i < this->bluePlayer.inGame() && !moved; ++i) {
            if(this->bluePlayer.almostDone(this->bluePlayer.tokensInGame[i]) && !this->bluePlayer.immovable(this->bluePlayer.tokensInGame[i], this->dice.diceValue + 1)) {
                bool finished = false;
                this->bluePlayer.move(this->bluePlayer.tokensInGame[i], this->dice.diceValue + 1, finished);
                moved = true;
                this->redPlayer.back(this->bluePlayer.tokensInGame[i].line, this->bluePlayer.tokensInGame[i].col);
                this->bluePlayer.place(this->bluePlayer.tokensInGame[i], this->bluePlayer.tokensInGame[i].line, this->bluePlayer.tokensInGame[i].col);
                if(this->bluePlayer.tokensInGame[i].final()) {
                    this->bluePlayer.tokensInGame[i].setPosition(this->bluePlayer.finishTiles[this->bluePlayer.out()].getPosition());
                    this->bluePlayer.tokensOut.push_back( this->bluePlayer.tokensInGame[i]);
                    this->bluePlayer.tokensInGame.erase(this->bluePlayer.tokensInGame.begin() + i);
                }
            }
        }

        if(!moved and this->bluePlayer.canMove(this->dice.diceValue + 1)) {
            // generez un indice random pt un token mutabil
            while(!moved) {
                int index = bluePlayer.random();
                if(!this->bluePlayer.immovable(this->bluePlayer.tokensInGame[index], this->dice.diceValue)) {
                    bool finished = false;
                    this->bluePlayer.move(this->bluePlayer.tokensInGame[index], this->dice.diceValue + 1, finished);
                    moved = true;
                    if(this->bluePlayer.tokensInGame[index].final()) {
                        this->bluePlayer.tokensInGame[index].setPosition(this->bluePlayer.finishTiles[this->bluePlayer.out()].getPosition());
                        this->bluePlayer.tokensOut.push_back( this->bluePlayer.tokensInGame[index]);
                        this->bluePlayer.tokensInGame.erase(this->bluePlayer.tokensInGame.begin() + index);
                    }
                    else {
                        this->redPlayer.back(this->bluePlayer.tokensInGame[index].line, this->bluePlayer.tokensInGame[index].col);
                        this->bluePlayer.place(this->bluePlayer.tokensInGame[index], this->bluePlayer.tokensInGame[index].line, this->bluePlayer.tokensInGame[index].col);
                    }
                }
            }
        }
    }
}

void Game::update(int turn) {
    if(turn == 0) { // muta rosu
        this->redTurn();
    }
    else { // muta albastru
        this->blueTurn();
    }
}
