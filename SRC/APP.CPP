#include "APP.H"
#include "RENDERER.H"
#include "CUBE.H"
#include "TIMER.H"
#include "UI.H"

App::App() {
    renderer = new Renderer();

    cube = new Cube();

    ui = new UI();

    initTimer();

    isRunning = 1;

    fps = frames = lastTime = 0;
}

App::~App() {
    delete renderer;

    delete cube;

    delete ui;

    exitTimer();
}

void App::loop(void) {
     while (isRunning) {
        processInput();
        update();
        render();
    }
}

void App::processInput(void) {

}

void App::update(void) {
    frames++;
    // runs every second
    unsigned int currentTime = getTick();
    if (currentTime - lastTime >= SECOND) {
        lastTime = currentTime;
		fps = frames;
		frames = 0;
	}

    ui->update(fps);
    
    cube->update();
}

void App::render(void) {
    renderer->clear(BLACK);

    ui->draw(renderer);
    
    cube->draw(renderer);

    renderer->updateBuffer();
}
