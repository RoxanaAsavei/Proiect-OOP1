#ifndef OOP_BLUEPLAYER_H
#define OOP_BLUEPLAYER_H


#include "Player.h"

class BluePlayer : public Player{
private:
    void initPlayer();
public:
    BluePlayer();
    void move(Token& token, int value, bool& finished);
    static bool immovable(const Token &token, int move);
    static bool almostDone(const Token &token);
    int random();

    bool canMove(int i);
};

#endif //OOP_BLUEPLAYER_H