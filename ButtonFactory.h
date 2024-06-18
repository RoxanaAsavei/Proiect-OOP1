#ifndef OOP_BUTTONFACTORY_H
#define OOP_BUTTONFACTORY_H

#include "Button.h"

class ButtonFactory {
public:
    static Button noPlayers(const std::string& no);
    static Button start();
};


#endif //OOP_BUTTONFACTORY_H
