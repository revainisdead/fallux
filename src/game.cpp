#include <iostream>
#include "constants.h"
#include "game.h"

using namespace irr;

// Values local to this value that determine pickablility,
// based upon IDs in ISceneNode.
enum
{
    ID_IsNotPickable = 0,
    IDFlag_IsPickable = 1 << 0,
    IDFlag_IsHighlightable = 1 << 1,
};

Game::Game() {
    setup();
    setup_nodes();
    setup_camera();
}

Game::~Game() {
    device->drop();
    selector->drop();
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
    for(std::vector<scene::IAnimatedMesh*>::iterator it = meshes.begin(); it != meshes.end(); ++it) {
        node = smgr->addOctreeSceneNode((*it)->getMesh(0), 0, IDFlag_IsPickable, 1024);
        nodes.push_back(node);
        //node = smgr->addMeshSceneNode(mesh->getMesh(0));
    }

    // The map doesn't start the player at the center of the map, move it.
    if (nodes[0])
        node->setPosition(core::vector3df(-1300, -144, -1249));

        selector = smgr->createOctreeTriangleSelector(meshes[0]->getMesh(0), nodes[0], 128);
        nodes[0]->setTriangleSelector(selector);
}

void Game::setup_camera() {
    int keyMapSize = 5;
    SKeyMap keyMap[keyMapSize];

    // Forward
    keyMap[0].Action = EKA_MOVE_FORWARD;
    keyMap[0].KeyCode = KEY_KEY_W;
    // Backward
    keyMap[1].Action = EKA_MOVE_BACKWARD;
    keyMap[1].KeyCode = KEY_KEY_S;
    // Left
    keyMap[2].Action = EKA_STRAFE_LEFT;
    keyMap[2].KeyCode = KEY_KEY_A;
    // Right
    keyMap[3].Action = EKA_STRAFE_RIGHT;
    keyMap[3].KeyCode = KEY_KEY_D;
    // Jump
    keyMap[4].Action = EKA_JUMP_UP;
    keyMap[4].KeyCode = KEY_SPACE;

    camera = smgr->addCameraSceneNodeFPS(
        0,          // parent
        160.0f,     // rotateSpeed
        0.5f,       // moveSpeed
        -1,         // id
        keyMap,     // keyMapArray
        keyMapSize, // keyMapSize
        false,      // noVerticalMovement
        4.0f,      // jumpSpeed
        false,      // invertMouse
        true        // makeActive
    );
    camera->setPosition(core::vector3df(50, 50, -60));
    camera->setTarget(core::vector3df(-70, 30, -60));

    if (selector) {
        scene::ISceneNodeAnimator *anim = smgr->createCollisionResponseAnimator(
            selector, camera, core::vector3df(30, 50, 30),
            core::vector3df(0, GRAVITY_CON, 0), core::vector3df(0, 30, 0));
        // drop selector???
        camera->addAnimator(anim);
        // drop anim in destructor? only if it doesn't need to be saved.
        anim->drop();
    }

    // Lock mouse movement to camera.
    device->getCursorControl()->setVisible(false);


}

void Game::update() {
    if (device->isWindowActive()) {
        driver->beginScene(true, true, video::SColor(255, 200, 200, 200));
        smgr->drawAll();
        driver->endScene();
        device->setWindowCaption(caption.c_str());
    } else {
        device->yield();
    }
}

void Game::run() {
    //game.driver->getFPS();
    //game.driver->getName();
    while(device->run()) {
        update();
    }
}
