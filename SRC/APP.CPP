#include "APP.H"
#include "RENDERER.H"
#include "CUBE.H"
#include "TIMER.H"
#include "UI.H"
#include "KEYBRD.H"

App::App() {
    rndInit();

    cube = new Cube();

    //ui = new UI();

    _initTimer();

    kbInit();

    isRunning = 1;

    fps = frames = lastTime = 0;
}

App::~App() {
    rndExit();

    delete cube;

    //delete ui;

    _exitTimer();

    kbExit();
}

void App::loop(void) {
     while (isRunning) {
        processInput();
        update();
        render();
    }
}

void App::processInput(void) {
    char key = kbHit();

    if (key == ESC) {
        isRunning = 0;
    }
}

void App::update(void) {
    // frames++;
    
    // unsigned int currentTime = _getTick();
    // // runs every second
    // if (currentTime - lastTime >= TICKS_PER_SECOND) {
    //     lastTime = currentTime;
    //     fps = frames;
    //     frames = 0;
    // }

    //ui->update(fps);

    cube->update();
}

void App::render(void) {
    rndClear(0x0);

    //ui->draw(renderer);
    

    cube->draw();

    rndUpdateBuffer();
}
