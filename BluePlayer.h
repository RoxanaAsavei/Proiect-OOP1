#ifndef OOP_BLUEPLAYER_H
#define OOP_BLUEPLAYER_H


#include "Player.h"

class BluePlayer : public Player{
private:
    void initPlayer();
public:
    BluePlayer();
    void move(Token& token, int value, bool& finished);
    static bool immovable(Token &token, int move);
    bool almostDone(Token &token);
    int random();
};

#endif //OOP_BLUEPLAYER_H