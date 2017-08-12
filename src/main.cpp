#include <irrlicht.h>
#include <iostream>
#include <stdio.h>

using namespace irr;


int main() {
    video::E_DRIVER_TYPE driverType = video::EDT_OPENGL;

    IrrlichtDevice *device = createDevice(driverType, core::dimension2d<u32>(640, 480));
    if (device == 0) return 1;

    video::IVideoDriver *driver = device->getVideoDriver();
    scene::ISceneManager *smgr = device->getSceneManager();

    // Debug current directory
    io::path working_dir = device->getFileSystem()->getWorkingDirectory();
    std::cout << working_dir.c_str() << std::endl;

    device->getFileSystem()->addFileArchive("res/meshes/map-20kdm2.pk3");

    scene::IAnimatedMesh *mesh = smgr->getMesh("20kdm2.bsp");
    scene::ISceneNode *node = 0;

    if (mesh)
        //node = smgr->addOctreeSceneNode(mesh->getMesh(0), 0, -1, 1024);
        node = smgr->addMeshSceneNode(mesh->getMesh(0));

    if (node)
        node->setPosition(core::vector3df(-1300, -144, -1249));

    smgr->addCameraSceneNodeFPS();
    device->getCursorControl()->setVisible(false);

    int lastFPS = -1;
    core::stringw caption = L"";
    while(device->run()) {
        if (device->isWindowActive()) {
            driver->beginScene(true, true, video::SColor(255, 200, 200, 200));
            smgr->drawAll();
            driver->endScene();

            int fps = driver->getFPS();

            if (lastFPS != fps) {
                caption = L"Quake 3 Map [";
                caption += driver->getName();
                caption += "] FPS: " + fps;
            }

            device->setWindowCaption(caption.c_str());
            lastFPS = fps;
        } else {
            device->yield();
        }
    }

    device->drop();
    //game.shutdown() // game holds device.
    return 0;
}
