#ifndef OOP_GREENPLAYER_H
#define OOP_GREENPLAYER_H

#include "Player.h"

class GreenPlayer : public Player{
private:
    void initPlayer();
public:
    GreenPlayer();
    ~GreenPlayer() override {
        std::cout << "Destructor GreenPlayer\n";
    }
};


#endif //OOP_GREENPLAYER_H
