#include <irrlicht.h>
#include <iostream>
#include <stdio.h>
#include "event.h"
#include "game.h"


static const std::string MESHES_DIR="res/meshes";

using namespace irr;

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
    device->getFileSystem()->addFileArchive(MESHES_DIR + "/map-20kdm2.pk3");
    */
    Game game;


    scene::IAnimatedMesh *mesh = game.smgr->getMesh("20kdm2.bsp");
    scene::ISceneNode *node = 0;

    if (mesh)
        //node = smgr->addOctreeSceneNode(mesh->getMesh(0), 0, -1, 1024);
        node = game.smgr->addMeshSceneNode(mesh->getMesh(0));

    if (node)
        node->setPosition(core::vector3df(-1300, -144, -1249));

    game.smgr->addCameraSceneNodeFPS();
    game.device->getCursorControl()->setVisible(false);

    int lastFPS = -1;
    core::stringw caption = L"";
    while(game.device->run()) {
        if (game.device->isWindowActive()) {
            game.driver->beginScene(true, true, video::SColor(255, 200, 200, 200));
            game.smgr->drawAll();
            game.driver->endScene();

            int fps = game.driver->getFPS();

            if (lastFPS != fps) {
                caption = L"Quake 3 Map [";
                caption += game.driver->getName();
                caption += "] FPS: " + fps;
            }

            game.device->setWindowCaption(caption.c_str());
            lastFPS = fps;
        } else {
            game.device->yield();
        }
    }

    //game.shutdown() // game holds device.
    return 0;
}
