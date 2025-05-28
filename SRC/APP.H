#ifndef APP_H
#define APP_H

class Renderer;
class Cube;
class UI;
class App {
public:
    App();
    
    ~App();

    void loop(void);

private:
    void processInput(void);

    void update(void);

    void render(void);

    const Renderer* renderer;

    Cube* cube;

    UI* ui;

    int isRunning;

    unsigned int fps, frames, lastTime;
};

#endif