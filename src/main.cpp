#include <iostream>
#include <irrlicht.h>

using namespace irr;
int main() {
    std::cout << "test out" << std::endl;

    IrrlichtDevice *device = createDevice(video::EDT_SOFTWARE, core::dimension2d<u32>(640, 480), 16, false, false, false, 0);

    if (!device)
        return 1;

    device->setWindowCaption(L"Irrlicht Engine");

    video::IVideoDriver *driver = device->getVideoDriver();
    scene::ISceneManager *smgr = device->getSceneManager();
    gui::IGUIEnvironment *guienv = device->getGUIEnvironment();

    guienv->addStaticText(L"Hello World!", core::rect<s32>(10, 10, 260, 22), true);

    // TODO: Fix this absolute path later.
    scene::IAnimatedMesh *mesh = smgr->getMesh("/home/christian/bin/fallux/res/meshes/sydney.md2");
    if (!mesh) {
        device->drop();
        return 1;
    }
    scene::IAnimatedMeshSceneNode *node = smgr->addAnimatedMeshSceneNode(mesh);

    if (node) {
        node->setMaterialFlag(video::EMF_LIGHTING, false);
        node->setMD2Animation(scene::EMAT_STAND);
        node->setMaterialTexture(0, driver->getTexture("/home/christian/bin/fallux/res/textures/sydney.bmp"));
    }

    smgr->addCameraSceneNode(0, core::vector3df(0, 30, -40), core::vector3df(0, 5, 0));

    while (device->run()) {
        driver->beginScene(true, true, video::SColor(255, 100, 101, 140));

        smgr->drawAll();
        guienv->drawAll();

        driver->endScene();
    }

    device->drop();
    return 0;
}
