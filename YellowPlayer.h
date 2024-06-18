

#ifndef OOP_YELLOWPLAYER_H
#define OOP_YELLOWPLAYER_H
#include "Player.h"

class YellowPlayer : public Player {
private:
    void initPlayer(AssetsManager& assetsManager);
public:
    explicit YellowPlayer(AssetsManager& assetsManager);
    ~YellowPlayer() override {
        std::cout << "Destructor YellowPlayer\n";
    }

};


#endif //OOP_YELLOWPLAYER_H
