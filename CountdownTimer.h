#ifndef OOP_COUNTDOWNTIMER_H
#define OOP_COUNTDOWNTIMER_H
#include <SFML/Graphics.hpp>

class CountdownTimer {
private:
    sf::Time timeRemaining;
    sf::Text text;

    void updateText();
public:
    CountdownTimer(int seconds, const sf::Font& font);

    void update(sf::Time deltaTime);

    void draw(sf::RenderWindow& window);

    bool isFinished() const;
};

#endif //OOP_COUNTDOWNTIMER_H