#include "game.h"


Game::Game() {
    setup();
}

Game::~Game() {
    device->drop();
}

void Game::setup() {
    video::E_DRIVER_TYPE videoDriver = video::EDT_OPENGL;
    device = createDevice(videoDriver, core::dimension2d<u32>(640, 480));
    if (!device) return;

    driver = device->getVideoDriver();
    msgr = device->getSceneManager();

    working_dir = device->getFileSystem()->getWorkingDirectory();
    std::cout << working_dir.c_str() << std::endl;
}

void Game::run() {
    return;
}
