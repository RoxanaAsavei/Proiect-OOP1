#ifndef OOP_COUNTDOWNTIMER_H
#define OOP_COUNTDOWNTIMER_H
#include <SFML/Graphics.hpp>

class CountdownTimer {
private:
    sf::Time timeRemaining;
    sf::Text text;

    void updateText();
public:
    [[maybe_unused]] CountdownTimer(int seconds, const sf::Font& font);

    [[maybe_unused]] void update(sf::Time deltaTime);

    [[maybe_unused]] void draw(sf::RenderWindow& window);

    [[maybe_unused]] bool isFinished() const;
};

#endif //OOP_COUNTDOWNTIMER_H
