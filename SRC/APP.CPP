#include "APP.H"
#include <IOSTREAM.H>
#include "RENDERER.H"
#include "CUBE.H"

App::App() {
    renderer = new Renderer();

    cube = new Cube();

    isRunning = 1;
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
    cube->update();
}

void App::render(void) {
    renderer->clear(BLACK);
    cout << "test;";
   
    cube->draw(renderer);

    renderer->updateBuffer();
}
