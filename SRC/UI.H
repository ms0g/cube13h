#ifndef UI_H
#define UI_H

class Renderer;
class UI {
public:
    UI();

    void update(unsigned int fps);
    
    void draw(Renderer* renderer);

private:
    struct UIElement {
        struct {
            int x;
            int y;
        } position;
      
        int val;

        char color;
    };

    void drawText(const char* s, int x, int y, char color, Renderer* renderer);
    
    void drawNumber(int value, int x, int y, char color, Renderer* renderer);

    UIElement fpsText;
    UIElement fpsNum;
};

#endif