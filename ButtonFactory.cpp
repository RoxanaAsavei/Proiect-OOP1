#include "ButtonFactory.h"

Button ButtonFactory::noPlayers(const std::string &no) {
    return Button(no, {300, 180}, 50, sf::Color{2,71,77}, sf::Color::White);
}

Button ButtonFactory::start() {
    return Button("START", {300, 220}, 70, sf::Color::White, sf::Color{2,71,77});
}
