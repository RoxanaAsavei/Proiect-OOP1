#include "CountdownTimer.h"

CountdownTimer::CountdownTimer(int seconds, const sf::Font &font) : timeRemaining(sf::seconds(seconds)) {
    text.setFont(font);
    text.setCharacterSize(30);
    text.setOutlineThickness(2.f);
    text.setOutlineColor(sf::Color::Black);
    text.setFillColor(sf::Color(180, 55, 87));
    updateText();
}

void CountdownTimer::updateText() {
    int totalSeconds = static_cast<int>(timeRemaining.asSeconds());
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    text.setString("Remaining time: " + std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds));
    text.setPosition(60, 60);
}

void CountdownTimer::update(sf::Time deltaTime) {
    if (timeRemaining > sf::Time::Zero) {
        timeRemaining -= deltaTime;
        if (timeRemaining < sf::Time::Zero) {
            timeRemaining = sf::Time::Zero;
        }
        updateText();
    }
}

void CountdownTimer::draw(sf::RenderWindow &window) {
    window.draw(text);
}

bool CountdownTimer::isFinished() const {
    return timeRemaining == sf::Time::Zero;
}