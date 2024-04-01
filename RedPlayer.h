#ifndef OOP_REDPLAYER_H
#define OOP_REDPLAYER_H
#include "Player.h"

class RedPlayer : public Player{

private:
    void initPlayer();

public:
    RedPlayer();
    void move(Token& token, int value, bool &finished);
    static bool immovable(Token &token, int move);
};


#endif //OOP_REDPLAYER_H