#ifndef APP_H
#define APP_H

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

    Cube* cube;

    UI* ui;

    int isRunning;

    unsigned int fps, frames, lastTime;
};

#endif