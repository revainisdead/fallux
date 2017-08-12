#include <irrlicht.h>
#include <iostream>
#include <stdio.h>
#include "event.h"
#include "game.h"

using namespace irr;
static const core::stringw MESHES_DIR=L"res/meshes";

int main() {
    /*
    video::E_DRIVER_TYPE driverType = video::EDT_OPENGL;
    IrrlichtDevice *device = createDevice(driverType, core::dimension2d<u32>(640, 480));
    if (device == 0) return 1;
    video::IVideoDriver *driver = device->getVideoDriver();
    scene::ISceneManager *smgr = device->getSceneManager();
    // Debug current directory
    io::path working_dir = device->getFileSystem()->getWorkingDirectory();
    std::cout << working_dir.c_str() << std::endl;
    */

    Game game;
    game.run();
    return 0;
}
