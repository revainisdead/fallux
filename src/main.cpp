#include <irrlicht.h>
#include <iostream>
#include <stdio.h>
#include "game.h"

using namespace irr;

int main() {
    Game game;
    game.run();

    s32 t1 = 1 << 0;
    s32 t2 = 1 << 1;
    std::cout << t1 << std::endl;
    std::cout << t2 << std::endl;

    return 0;
}
