#ifndef OOP_REDPLAYER_H
#define OOP_REDPLAYER_H
#include "Player.h"


class RedPlayer : public Player{
private:
    void initPlayer(AssetsManager& assetsManager);

public:
    explicit RedPlayer(AssetsManager& assetsManager);
    ~RedPlayer() override {
        std::cout << "Destructor RedPlayer\n";
    }


    void displayDice(sf::RenderWindow& window, class Game& game) override;
    void updateTokens(int &line, int &col, sf::RenderWindow &window) override;
    static void displayText(sf::RenderWindow& window);
};


#endif //OOP_REDPLAYER_H