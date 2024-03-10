#include "APP.H"
#include <IOSTREAM.H>
#include "RENDERER.H"
#include "CUBE.H"
#include "UI.H"

App::App() {
    renderer = new Renderer();

    cube = new Cube();

    ui = new UI();

    isRunning = 1;

    fps = 60;
}

App::~App() {
    delete renderer;

    delete cube;
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
    ui->update(fps);
    cube->update();
}

void App::render(void) {
    renderer->clear(BLACK);

    ui->draw(renderer);
    
    cube->draw(renderer);

    renderer->updateBuffer();
}
