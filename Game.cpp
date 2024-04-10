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
                    Token& t = this->redPlayer.getTokenInHouse(i);
                    if(t.clickedOn(this->mousePosView)) {
                        moved = true;
                        clickedUpon = true;
                        this->redPlayer.updateFree((t.getShapePos()));
                        // get it out of house
                        t.setLine(13);
                        t.setCol(6);
                        this->bluePlayer.back(13, 6);
                        this->redPlayer.place(t, 13, 6);
                        // place it in game
                        this->redPlayer.addTokenInGame(t);
                        // token no longer in house
                        this->redPlayer.eraseFromInHouse(i);
                    }

                }
            }
        }
    }

    else {
        int diceValue = this->dice.getDiceValue();
        if(this->redPlayer.inGame() and this->redPlayer.canMove(diceValue + 1)) { // if the redPlayer still has tokens in game
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
                        Token& t = this->redPlayer.getTokenInGame(i);
                        if(t.clickedOn(this->mousePosView) && !this->redPlayer.immovable(t, diceValue + 1)) {
                            moved = true;
                            clickedUpon = true;
                            bool finished = false;
                            int lineBefore = t.getLine();
                            int colBefore = t.getCol();
                            this->redPlayer.move(t, diceValue + 1, finished);
                            int lineAfter = t.getLine();
                            int colAfter = t.getCol();
                            this->bluePlayer.back(lineAfter, colAfter);
                            this->redPlayer.place(t, lineAfter, colAfter);
                            this->redPlayer.resize(lineBefore, colBefore);
                            if(t.final()) {
                                t.setPosition(this->redPlayer.outPosition());
                                this->redPlayer.takeTokenOut(t);
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
        Token& t = this->bluePlayer.getTokenInHouse(0);
        t.setLine(8);
        t.setCol(13);
        this->bluePlayer.updateFree(t.getShapePos());
        this->redPlayer.back(8, 13);
        this->bluePlayer.place(t, 8, 13);
        // place it in game
        this->bluePlayer.addTokenInGame(t);
        this->bluePlayer.eraseFromInHouse(0);
    }

    else { // trebuie sa mute unul dintre pionii din joc
        // vad daca am unul aproape de a intra in casa
        bool moved = false;
        int diceValue = this->dice.getDiceValue();
        for(int i = 0; i < this->bluePlayer.inGame() && !moved; ++i) {
            Token& t = this->bluePlayer.getTokenInGame(i);
            if(this->bluePlayer.almostDone(t) && !this->bluePlayer.immovable(t, diceValue + 1)) {
                bool finished = false;
                int lineBefore = t.getLine();
                int colBefore = t.getCol();
                this->bluePlayer.move(t, diceValue + 1, finished);
                moved = true;
                int lineAfter = t.getLine();
                int colAfter = t.getCol();
                this->redPlayer.back(lineAfter, colAfter);
                this->bluePlayer.place(t, lineAfter, colAfter);
                this->bluePlayer.resize(lineBefore, colBefore);
                if(t.final()) {
                    t.setPosition(this->bluePlayer.outPosition());
                    this->bluePlayer.takeTokenOut(t);
                    this->bluePlayer.eraseFromInGame(i);
                }
            }
        }

        if(!moved and this->bluePlayer.canMove(diceValue + 1)) {
            // generez un indice random pt un token mutabil
            while(!moved) {
                int index = bluePlayer.random();
                Token& t = this->bluePlayer.getTokenInGame(index);
                if(!this->bluePlayer.immovable(t, diceValue + 1)) {
                    bool finished = false;
                    int lineBefore = t.getLine();
                    int colBefore = t.getCol();
                    this->bluePlayer.move(t, diceValue + 1, finished);
                    moved = true;
                    if(t.final()) {
                        t.setPosition(this->bluePlayer.outPosition());
                        this->bluePlayer.takeTokenOut( t);
                        this->bluePlayer.eraseFromInGame(index);
                    }
                    else {
                        int lineAfter = t.getLine();
                        int colAfter = t.getCol();
                        this->redPlayer.back(lineAfter, colAfter);
                        this->bluePlayer.place(t, lineAfter, colAfter);
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
    font.loadFromFile("assets/Davis_Preview.ttf");
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