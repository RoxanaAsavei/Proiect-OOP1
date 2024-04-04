#include "Game.h"

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
        this->winner("red");
        this->endGame = true;
    }

}

void Game::updateTokensRed() {

    // daca da 6 si mai are in casa, e obligat sa scoata din casa
    if(this->dice.getDiceValue() == 5 and this->redPlayer.inHouse()) {
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
                    if(this->redPlayer.clickedOnInHouse(i, this->mousePosView)) {
                        moved = true;
                        clickedUpon = true;
                        this->redPlayer.updateFree((this->redPlayer.getPositionInHouse(i)));
                        // get it out of house
                        this->redPlayer.setLineInHouse(i, 13);
                        this->redPlayer.setColInHouse(i, 6);
                        this->bluePlayer.back(this->redPlayer.getLineInHouse(i), this->redPlayer.getColInHouse(i));
                        this->redPlayer.place(this->redPlayer.getTokenInHouse(i), this->redPlayer.getLineInHouse(i), this->redPlayer.getColInHouse(i));
                        // place it in game
                        this->redPlayer.addTokenInGame(this->redPlayer.getTokenInHouse(i));
                        // token no longer in house
                        this->redPlayer.eraseFromInHouse(i);
                    }

                }
            }
        }
    }

    else {
        if(this->redPlayer.inGame() and this->redPlayer.canMove(this->dice.getDiceValue() + 1)) { // if the redPlayer still has tokens in game
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
                        if(this->redPlayer.clickedOnInGame(i, this->mousePosView) && !this->redPlayer.immovable(this->redPlayer.getTokenInGame(i), this->dice.getDiceValue() + 1)) {
                            moved = true;
                            clickedUpon = true;
                            bool finished = false;
                            int lineBefore = this->redPlayer.getLineInGame(i);
                            int colBefore = this->redPlayer.getColInGame(i);
                            this->redPlayer.move(this->redPlayer.getTokenInGame(i),this->dice.getDiceValue() + 1, finished);
                            this->bluePlayer.back(this->redPlayer.getLineInGame(i), this->redPlayer.getColInGame(i));
                            this->redPlayer.place(this->redPlayer.getTokenInGame(i), this->redPlayer.getLineInGame(i), this->redPlayer.getColInGame(i));
                            this->redPlayer.resize(lineBefore, colBefore);
                            if(this->redPlayer.getTokenInGame(i).final()) {
                                this->redPlayer.getTokenInGame(i).setPosition(this->redPlayer.outPosition());
                                this->redPlayer.takeTokenOut(this->redPlayer.getTokenInGame(i));
                                this->redPlayer.eraseFromInGame(i);
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
        this->winner("blue");
        this->endGame = true;
    }
}

void Game::updateTokensBlue() {
    if(this->dice.getDiceValue() == 5 and this->bluePlayer.inHouse()) { // e obligat sa scoata din casa
        this->bluePlayer.setLineInHouse(0, 8);
        this->bluePlayer.setColInHouse(0, 13);
        this->bluePlayer.updateFree(this->bluePlayer.getPositionInHouse(0));
        this->redPlayer.back(this->bluePlayer.getLineInHouse(0), this->bluePlayer.getColInHouse(0));
        this->bluePlayer.place(this->bluePlayer.getTokenInHouse(0), this->bluePlayer.getLineInHouse(0), this->bluePlayer.getColInHouse(0));
        // place it in game
        this->bluePlayer.addTokenInGame(this->bluePlayer.getTokenInHouse(0));
        this->bluePlayer.eraseFromInHouse(0);
    }

    else { // trebuie sa mute unul dintre pionii din joc
        // vad daca am unul aproape de a intra in casa
        bool moved = false;
        for(int i = 0; i < this->bluePlayer.inGame() && !moved; ++i) {
            if(this->bluePlayer.almostDone(this->bluePlayer.getTokenInGame(i)) && !this->bluePlayer.immovable(this->bluePlayer.getTokenInGame(i), this->dice.getDiceValue() + 1)) {
                bool finished = false;
                int lineBefore = this->bluePlayer.getLineInGame(i);
                int colBefore = this->bluePlayer.getColInGame(i);
                this->bluePlayer.move(this->bluePlayer.getTokenInGame(i), this->dice.getDiceValue() + 1, finished);
                moved = true;
                this->redPlayer.back(this->bluePlayer.getLineInGame(i), this->bluePlayer.getColInGame(i));
                this->bluePlayer.place(this->bluePlayer.getTokenInGame(i), this->bluePlayer.getLineInGame(i), this->bluePlayer.getColInGame(i));
                this->bluePlayer.resize(lineBefore, colBefore);
                if(this->bluePlayer.getTokenInGame(i).final()) {
                    this->bluePlayer.getTokenInGame(i).setPosition(this->bluePlayer.outPosition());
                    this->bluePlayer.takeTokenOut(this->bluePlayer.getTokenInGame(i));
                    this->bluePlayer.eraseFromInGame(i);
                }
            }
        }

        if(!moved and this->bluePlayer.canMove(this->dice.getDiceValue() + 1)) {
            // generez un indice random pt un token mutabil
            while(!moved) {
                int index = bluePlayer.random();
                if(!this->bluePlayer.immovable(this->bluePlayer.getTokenInGame(index), this->dice.getDiceValue() + 1)) {
                    bool finished = false;
                    int lineBefore = this->bluePlayer.getLineInGame(index);
                    int colBefore = this->bluePlayer.getColInGame(index);
                    this->bluePlayer.move(this->bluePlayer.getTokenInGame(index), this->dice.getDiceValue() + 1, finished);
                    moved = true;
                    if(this->bluePlayer.getTokenInGame(index).final()) {
                        this->bluePlayer.getTokenInGame(index).setPosition(this->bluePlayer.outPosition());
                        this->bluePlayer.takeTokenOut( this->bluePlayer.getTokenInGame(index));
                        this->bluePlayer.eraseFromInGame(index);
                    }
                    else {
                        this->redPlayer.back(this->bluePlayer.getLineInGame(index), this->bluePlayer.getColInGame(index));
                        this->bluePlayer.place(this->bluePlayer.getTokenInGame(index), this->bluePlayer.getLineInGame(index), this->bluePlayer.getColInGame(index));
                    }
                    this->bluePlayer.resize(lineBefore, colBefore);
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

void Game::winner(const std::string& playerColor) {
    sf::Font font;
    font.loadFromFile("Davis_Preview.ttf");
    sf::Text text;
    text.setFont(font);
    if(playerColor == "red") {
        text.setString("RED\nWON!");
        text.setFillColor(sf::Color::Red);
    }
    else {
        text.setString("BLUE\nWON!");
        text.setFillColor(sf::Color::Blue);
    }
    text.setCharacterSize(120);
    text.setOutlineThickness(3.f);
    text.setOutlineColor(sf::Color::Black);
    text.setPosition(5 * squareSize + offset_ox, 5 * squareSize + offset_oy);
    this->window->clear(sf::Color{163, 228, 215});
    this->window->draw(text);
    this->window->display();
    sf::sleep(sf::seconds(3));
}
