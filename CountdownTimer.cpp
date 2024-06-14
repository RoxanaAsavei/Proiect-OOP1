#include "CountdownTimer.h"

CountdownTimer::CountdownTimer(int seconds, const sf::Font &font) {
    timeRemaining = sf::seconds(seconds);

    // Initialize the text
    text.setFont(font);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White);
    updateText();
}

void CountdownTimer::updateText() {
    int totalSeconds = static_cast<int>(timeRemaining.asSeconds());
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    text.setString(std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds));
    text.setPosition(10, 10);
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

