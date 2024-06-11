#ifndef OOP_REDPLAYER_H
#define OOP_REDPLAYER_H
#include "Player.h"

class RedPlayer : public Player{
private:
    void initPlayer();

public:
    RedPlayer();
    ~RedPlayer() override {
        std::cout << "Destructor RedPlayer\n";
    }
 /*   std::shared_ptr<Player> clone() const override {
        return std::make_shared<RedPlayer(*this)>();
    }
    */
    void displayDice(sf::RenderWindow& window) override;
    void updateTokens(int &line, int &col, sf::RenderWindow &window) override;
    void displayText(sf::RenderWindow& window);
};


#endif //OOP_REDPLAYER_H