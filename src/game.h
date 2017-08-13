#ifndef GAME_H
#define GAME_H

#include <irrlicht.h>
#include <vector>
#include "constants.h"
#include "event.h"


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
        void setup_nodes();
        void setup_camera();
        // Potentially let this return a stack trace if a failure occurs.
        void run();
        // Maybe later for shutting down things outside this object.
        //void shutdown();

    private:
        void update();

        std::vector<scene::IAnimatedMesh*> meshes;
        std::vector<scene::ISceneNode*> nodes;

        IrrlichtDevice *device;
        video::IVideoDriver *driver;
        scene::ISceneManager *smgr;
        //EventReceiver event_r;
        scene::ITriangleSelector *selector;
        scene::ICameraSceneNode *camera;

        io::path working_dir;
        core::stringw caption;
};

#endif
