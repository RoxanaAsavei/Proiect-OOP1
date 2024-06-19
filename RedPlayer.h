#ifndef OOP_REDPLAYER_H
#define OOP_REDPLAYER_H
#include "Player.h"
#include "CountdownTimer.h"

class RedPlayer : public Player{
private:
    void initPlayer();

public:
    explicit RedPlayer(AssetsManager& assetsManager);
    ~RedPlayer() override {
        std::cout << "Destructor RedPlayer\n";
    }


    void displayDice(sf::RenderWindow& window, class Game& game) override;
    void updateTokens(int &line, int &col, sf::RenderWindow &window, class Game& game) override;
    static void displayText(sf::RenderWindow& window);
};


#endif //OOP_REDPLAYER_H