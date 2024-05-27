#ifndef OOP_REDPLAYER_H
#define OOP_REDPLAYER_H
#include "Player.h"

class RedPlayer : public Player{
private:
    void initPlayer();

public:
    RedPlayer();
    void displayDice(sf::RenderWindow& window) override;
    void updateTokens(int &line, int &col, sf::RenderWindow &window) override;
};


#endif //OOP_REDPLAYER_H