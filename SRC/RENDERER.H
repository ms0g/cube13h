#ifndef RENDERER_H
#define RENDERER_H

#ifdef __cplusplus
extern "C" {
#endif

void rndInit(void);

void rndExit(void);

void rndDDA(int x0, int y0, int x1, int y1, char color);
    
void rndBresenham(int x0, int y0, int x1, int y1, char color);

void rndDrawRect(int x, int y, int width, int height, char color);
    
void rndDrawTri(int x0, int y0, int x1, int y1, int x2, int y2, char color);

void rndDrawFilledTri(int x0, int y0, int x1, int y1, int x2, int y2, char color);

void rndClear(char color);

void rndUpdateBuffer(void);

#ifdef __cplusplus
}
#endif

#endif