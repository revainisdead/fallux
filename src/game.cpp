#include <iostream>
#include "game.h"

using namespace irr;

Game::Game() {
    setup();
    setup_nodes();
    setup_camera();
}

Game::~Game() {
    device->drop();
}

void Game::setup() {
    video::E_DRIVER_TYPE videoDriver = video::EDT_OPENGL;
    device = createDevice(videoDriver, core::dimension2d<u32>(640, 480));
    if (!device) return;

    driver = device->getVideoDriver();
    smgr = device->getSceneManager();

    working_dir = device->getFileSystem()->getWorkingDirectory();
    std::cout << working_dir.c_str() << std::endl;

    caption = L"Fallux - Irrlicht Engine";
}

void Game::setup_nodes() {
    device->getFileSystem()->addFileArchive("res/meshes/map-20kdm2.pk3");
    scene::IAnimatedMesh *mesh = smgr->getMesh("20kdm2.bsp");
    meshes.push_back(mesh);

    scene::ISceneNode *node = 0;
    //for(int i = meshes.begin(); i != meshes.end(); i++) {
    for(std::vector<scene::IAnimatedMesh*>::iterator it = meshes.begin(); it != meshes.end(); ++it) {
        node = smgr->addOctreeSceneNode((*it)->getMesh(0), 0, -1, 1024);
        nodes.push_back(node);
        //node = smgr->addMeshSceneNode(mesh->getMesh(0));
    }

    // The map doesn't start the player at the center of the map, move it.
    if (nodes[0])
        node->setPosition(core::vector3df(-1300, -144, -1249));
}


void Game::setup_camera() {
    smgr->addCameraSceneNodeFPS();
    device->getCursorControl()->setVisible(false);
}

void Game::run() {
    //game.driver->getFPS();
    //game.driver->getName();
    while(device->run()) {
        if (device->isWindowActive()) {
            driver->beginScene(true, true, video::SColor(255, 200, 200, 200));
            smgr->drawAll();
            driver->endScene();
            device->setWindowCaption(caption.c_str());
        } else {
            device->yield();
        }
    }
}
