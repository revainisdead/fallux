#ifndef GAME_H
#define GAME_H

#include <irrlicht.h>
#include <stdio.h>

using namespace irr;

class Game {
    /***
     * Game should hold the root device of irrlicht and be responsible for the
     * main game loop and any other initialization.
     ***/
    public:
        Game();
        ~Game();
        void setup();
        // Potential let this return a stack trace if a failure occurs.
        void run();
        // Maybe later for shutting down things outside this object.
        //void shutdown();
        IrrlichtDevice *device;
        video::IVideoDriver *driver;
        scene::ISceneManager *smgr;

    private:
        io::path working_dir;
};

#endif
