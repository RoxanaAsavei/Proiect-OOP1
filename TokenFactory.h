#ifndef OOP_TOKENFACTORY_H
#define OOP_TOKENFACTORY_H
#include "Token.h"

class TokenFactory {
public:
    static Token redToken();
    static Token blueToken();
    static Token yellowToken();
    static Token greenToken();
};


#endif //OOP_TOKENFACTORY_H
