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

    highlightedSceneNode = 0;

    //video::SMaterial material = *(new video::SMaterial());
    material.setTexture(0, 0);
    material.Lighting = false;
    material.Wireframe = true;

    setup_nodes();
    setup_camera();
    setup_guy();
    setup_billboard();
}

Game::~Game() {
    device->drop();
    selector->drop();
    guy_selector->drop();
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

        selector->drop();
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
        65.0f,     // rotateSpeed
        0.43f,       // moveSpeed
        -1,         // id
        keyMap,     // keyMapArray
        keyMapSize, // keyMapSize
        false,      // noVerticalMovement
        3.3f,      // jumpSpeed
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

void Game::setup_guy() {
    scene::IAnimatedMeshSceneNode *node = 0;

    node = smgr->addAnimatedMeshSceneNode(smgr->getMesh("res/meshes/ninja.b3d"), 0, IDFlag_IsPickable | IDFlag_IsHighlightable);
    node->setScale(core::vector3df(10));
    node->setPosition(core::vector3df(-75, -66, -80));
    node->setRotation(core::vector3df(0, 90, 0));
    node->setAnimationSpeed(8.f);
    node->getMaterial(0).NormalizeNormals = true;
    node->getMaterial(0).Lighting = true;
    guy_selector = smgr->createTriangleSelector(node);
    node->setTriangleSelector(guy_selector);



    // Setup light
    scene::ILightSceneNode *light = smgr->addLightSceneNode(0, core::vector3df(-60, 100, 400), video::SColorf(1.0f, 1.0f, 1.0f, 1.0f), 600.0f);
    light->setID(ID_IsNotPickable);

    collMgr = smgr->getSceneCollisionManager();
}

void Game::setup_billboard() {
    bill = smgr->addBillboardSceneNode();
    bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
    bill->setMaterialTexture(0, driver->getTexture("res/textures/particle.bmp"));
    bill->setMaterialFlag(video::EMF_LIGHTING, false);
    bill->setMaterialFlag(video::EMF_ZBUFFER, false);
    bill->setSize(core::dimension2d<f32>(20.0f, 20.0f));
    bill->setID(ID_IsNotPickable);
}

void Game::__reset_highlight() {
    if (highlightedSceneNode) {
        highlightedSceneNode->setMaterialFlag(video::EMF_LIGHTING, true);
        highlightedSceneNode = 0;
    }
}

void Game::__raycast_intersect() {
    core::line3d<f32> ray;
    ray.start = camera->getPosition();
    ray.end = ray.start + (camera->getTarget() - ray.start).normalize() * 1000.0f;

    core::vector3df intersection;
    core::triangle3df hitTriangle;

    scene::ISceneNode *selectedSceneNode =
        collMgr->getSceneNodeAndCollisionPointFromRay(
            ray,
            intersection,
            hitTriangle,
            IDFlag_IsPickable,
            0
        );

    if (selectedSceneNode) {
        bill->setPosition(intersection);

        // Reset transform before we can do our own render.
        driver->setTransform(video::ETS_WORLD, core::matrix4());
        driver->setMaterial(material);
        driver->draw3DTriangle(hitTriangle, video::SColor(0, 255, 0, 0));

        if ((selectedSceneNode->getID() && IDFlag_IsHighlightable) == IDFlag_IsHighlightable) {
            highlightedSceneNode = selectedSceneNode;
            highlightedSceneNode->setMaterialFlag(video::EMF_LIGHTING, false);
        }
    }
}

void Game::update() {
    if (device->isWindowActive()) {
        __reset_highlight();
        __raycast_intersect();

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
