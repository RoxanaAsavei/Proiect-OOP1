#include "RedPlayer.h"
#include "Game.h"
const int offset_ox = 480;
const int offset_oy = 60;
const int squareSize = 60;

RedPlayer::RedPlayer(AssetsManager& assetsManager) {
    this->initPlayer(assetsManager);
    dice.initDiceFaces(assetsManager.diceFaces(color));
}

void RedPlayer::initPlayer(AssetsManager& assetsManager) {
    this->color = "red";
    // adding all 4 tokens
    Token token1{this->color, assetsManager.getTokenTexture(color), assetsManager.getPositions(color)};
    // setting position for the in-house tokens
    token1.setPosition(sf::Vector2f(1 * squareSize + squareSize / 2 + offset_ox, 10 * squareSize + offset_oy));
    this->takenPositions.push_back(token1.getShapePos());
    this->tokensInHouse.push_back(token1);

    Token token2{this->color, assetsManager.getTokenTexture(color), assetsManager.getPositions(color)};
    token2.setPosition(sf::Vector2f(3 * squareSize + squareSize / 2 + offset_ox, 10 * squareSize + offset_oy));
    this->takenPositions.push_back(token2.getShapePos());
    this->tokensInHouse.push_back(token2);

    Token token3{this->color, assetsManager.getTokenTexture(color), assetsManager.getPositions(color)};
    token3.setPosition(sf::Vector2f(1 * squareSize + squareSize / 2 + offset_ox, 12 * squareSize + offset_oy));
    this->takenPositions.push_back(token3.getShapePos());
    this->tokensInHouse.push_back(token3);

    Token token4{this->color, assetsManager.getTokenTexture(color), assetsManager.getPositions(color)};
    token4.setPosition(sf::Vector2f(3 * squareSize + squareSize / 2 + offset_ox, 12 * squareSize + offset_oy));
    this->takenPositions.push_back(token4.getShapePos());
    this->tokensInHouse.push_back(token4);

    sf::RectangleShape square;
    square.setSize(sf::Vector2f(squareSize, squareSize));
    square.setFillColor(sf::Color::White);
    square.setOutlineColor(sf::Color::Red);
    square.setOutlineThickness(2.0f);
    square.setPosition(240, 720);
    this->finishTiles.push_back(square);
    square.setPosition(300, 720);
    this->finishTiles.push_back(square);
    square.setPosition(240, 780);
    this->finishTiles.push_back(square);
    square.setPosition(300, 780);
    this->finishTiles.push_back(square);
}

void RedPlayer::displayDice(sf::RenderWindow &window, Game& game) {
    // display dice so you see it
    this->pollEvents(window);
    window.clear(sf::Color{163, 228, 215});
    dice.renderDice(window);
    game.renderAddition();
    // you have to click on it
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    sf::RectangleShape diceFace = dice.getDiceFace();
    bool clickedUpon = false;
    while(!clickedUpon && this->running(window)) {
        this->pollEvents(window);
        if(!this->running(window)) {
            break;
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            mousePosWindow = sf::Mouse::getPosition(window);
            mousePosView = window.mapPixelToCoords(mousePosWindow);
            if(diceFace.getGlobalBounds().contains(mousePosView)) {
                clickedUpon = true;
                // rolling the dice for 5 times
                for(int i = 0; i < 5; ++i) {
                    this->pollEvents(window);
                    if(!this->running(window)) {
                        break;
                    }
                    window.clear(sf::Color{163, 228, 215});
                    dice.Roll();
                    dice.renderDice(window);
                    game.renderAddition();
                    sf::sleep(sf::milliseconds(200));
                }
            }
        }
    }
}

void RedPlayer::updateTokens(int &line, int &col, sf::RenderWindow &window) {
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    // daca da 6 si mai are in casa, e obligat sa scoata din casa
    if(this->dice.getDiceValue() == 5 and this->inHouse()) {
        bool clickedUpon = false;
        while(!clickedUpon && this->running(window)) {
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                mousePosWindow = sf::Mouse::getPosition(window);
                mousePosView = window.mapPixelToCoords(mousePosWindow); // iau pozitia curenta
                bool moved = false;
                for(int i = 0; i < this->inHouse() and !moved; ++i) {
                    this->pollEvents(window);
                    if(!this->running(window)) {
                        break;
                    }
                    Token& t = this->tokensInHouse[i];
                    if(t.clickedOn(mousePosView)) {
                        moved = true;
                        clickedUpon = true;
                        this->updateFree((t.getShapePos()));
                        // get it out of house
                        t.setIndex(0);
                        this->place(t, t.getCoord());
                        std::pair<int, int> pos = t.getCoord();
                        line = pos.first;
                        col = pos.second;
                        // place it in game
                        this->tokensInGame.emplace_back(t);
                        // token no longer in house
                        this->tokensInHouse.erase(this->tokensInHouse.begin() + i);
                    }

                }
            }
        }
    }

    else {
        int diceValue = this->dice.getDiceValue();
        if(this->inGame() and this->canMove(diceValue + 1)) { // if the redPlayer still has tokens in game
            bool clickedUpon = false;
            while(!clickedUpon && this->running(window)) {
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    mousePosWindow = sf::Mouse::getPosition(window);
                    mousePosView = window.mapPixelToCoords(mousePosWindow);
                    bool moved = false;
                    for(int i = 0; i < this->inGame() && !moved; ++i) {
                        //......... // so i can close the window at any moment
                        this->pollEvents(window);
                        if(!this->running(window)) {
                            break;
                        }
                        Token& t = this->tokensInGame[i];
                        if(t.clickedOn(mousePosView) && !t.immovable(diceValue + 1)) {
                            moved = true;
                            clickedUpon = true;
                            bool finished = false;
                            t.setPrevPos();
                            t.move(diceValue + 1, finished);
                            std::pair<int, int> pos = t.getCoord();
                            line = pos.first;
                            col = pos.second;
                            this->place(t, t.getCoord());
                            this->resize(t.getPrev());
                            if(t.final()) {
                                t.setPosition(this->outPosition());
                                this->tokensOut.emplace_back(t);
                                this->tokensInGame.erase(this->tokensInGame.begin() + i);
                            }
                        }
                    }
                }
            }
        }
    }
}

void RedPlayer::displayText(sf::RenderWindow& window) {
    sf::Font font;
    if(!font.loadFromFile("assets/HoneyCrepes.ttf")) {
        throw fontError("assets/HoneyCrepes.ttf");
    }

    sf::Text text;
    text.setFont(font);
    std::string mesaj = "It's your\n    turn!";
    text.setString(mesaj);
    text.setFillColor(sf::Color(180, 55, 87));
    text.setCharacterSize(40);
    text.setOutlineThickness(2.f);
    text.setOutlineColor(sf::Color::Black);
    text.setPosition(4 * squareSize, 7 * squareSize + offset_oy);
    window.draw(text);
}


