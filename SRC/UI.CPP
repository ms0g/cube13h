#include "UI.H"
#include <stdlib.h>
#include <string.h>
#include "RENDERER.H"
#include "FONTS.H"

#define FPS_X 12
#define FPS_Y 10
#define FPS_ADJ 23
#define ADJ 6

UI::UI() {
    fpsText.position.x = FPS_X;
    fpsText.position.y = FPS_Y;
    fpsText.val = 0;
    fpsText.color = 0xF;

    fpsNum.position.x = FPS_X + FPS_ADJ;
    fpsNum.position.y = FPS_Y;
    fpsNum.val = 0;
    fpsNum.color = 0xF;

}

void UI::update(unsigned int fps) {
    fpsNum.val = fps;
}

void UI::draw(const Renderer* renderer) {
    drawText("FPS:", fpsText.position.x, fpsText.position.y, fpsText.color, renderer);
    drawNumber(fpsNum.val, fpsNum.position.x, fpsNum.position.y, fpsNum.color, renderer);
}

void UI::drawText(const char* s, int x, int y, char color, const Renderer* renderer) {
    for (int i = 0; i < strlen(s); ++i) {
        renderer->putchar(x, y, color, asciiFontTable[(int)s[i]]);
        x += ADJ;
    }
}

void UI::drawNumber(int value, int x, int y, char color, const Renderer* renderer) {
    char strNum[4];

    itoa(value, strNum, 10);
        
    drawText(strNum, x, y, color, renderer);
}