#ifndef OOP_BLUEPLAYER_H
#define OOP_BLUEPLAYER_H


#include "Player.h"

class BluePlayer : public Player{
private:
    void initPlayer(AssetsManager& assetsManager);
public:
    explicit BluePlayer(AssetsManager& assetsManager);
    ~BluePlayer() override {
        std::cout << "Destructor BluePlayer\n";
    }
};

#endif //OOP_BLUEPLAYER_H