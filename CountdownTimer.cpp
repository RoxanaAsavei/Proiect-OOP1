#include "CountdownTimer.h"

[[maybe_unused]] CountdownTimer::CountdownTimer(int seconds, const sf::Font &font) {
    timeRemaining = sf::seconds(seconds);

    // Initialize the text
    text.setFont(font);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White);
    updateText();
}

[[maybe_unused]] void CountdownTimer::updateText() {
    int totalSeconds = static_cast<int>(timeRemaining.asSeconds());
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    text.setString(std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds));
    text.setPosition(10, 10);
}

[[maybe_unused]] void CountdownTimer::update(sf::Time deltaTime) {
    if (timeRemaining > sf::Time::Zero) {
        timeRemaining -= deltaTime;
        if (timeRemaining < sf::Time::Zero) {
            timeRemaining = sf::Time::Zero;
        }
        updateText();
    }
}

[[maybe_unused]] void CountdownTimer::draw(sf::RenderWindow &window) {
    window.draw(text);
}

[[maybe_unused]] bool CountdownTimer::isFinished() const {
    return timeRemaining == sf::Time::Zero;
}

