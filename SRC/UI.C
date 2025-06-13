#include "UI.H"
#include "FONTS.H"
#include "RENDERER.H"

#define FPS_X 12
#define FPS_Y 10
#define FPS_ADJ 23
#define ADJ 6

typedef struct {
    struct {
        int x;
        int y;
    } position;
    
    union {
        int num;
        const char* str;
    } val;
    
    char color;
} UIElement;

static UIElement fpsText;
static UIElement fpsNum;

static void drawText(const char* s, int x, int y, char color);
static void drawNumber(int value, int x, int y, char color);

void uiInit(void) {
    fpsText.position.x = FPS_X;
    fpsText.position.y = FPS_Y;
    fpsText.val.str = "FPS:";
    fpsText.color = 0xF;

    fpsNum.position.x = FPS_X + FPS_ADJ;
    fpsNum.position.y = FPS_Y;
    fpsNum.val.num = 0;
    fpsNum.color = 0xF;
}

void uiUpdate(unsigned int fps) {
    fpsNum.val.num = fps;
}

void uiDraw(void) {
    drawText(fpsText.val.str, fpsText.position.x, fpsText.position.y, fpsText.color);
    drawNumber(fpsNum.val.num, fpsNum.position.x, fpsNum.position.y, fpsNum.color);
}

static void drawText(const char* s, int x, int y, char color) {
    int i;
    for (i = 0; i < strlen(s); ++i) {
        rndPutchar(x, y, color, asciiFontTable[(int)s[i]]);
        x += ADJ;
    }
}

static void drawNumber(int value, int x, int y, char color) {
    char strNum[4];

    itoa(value, strNum, 10);
        
    drawText(strNum, x, y, color);
}
