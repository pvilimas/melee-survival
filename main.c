#include <stdio.h>

#include "SDL2/SDL.h"

#include "graphics.h"

#define DEFAULT_BG &(Color4){140, 140, 140, 255}

void draw(Graphics *g) {
    // draw rect and lines
    G_SetColor(g, DEFAULT_BG);
    G_FillBG(g, NULL);
    G_DrawGrid(g, 200, &(Point2){100, 100}, &(Color4){0, 0, 0, 255});
    G_Update(g);
}

int main(int argc, char *argv[]) {

    (void) argc;
    (void) argv;

    Graphics g;

    G_Init(&g, DEFAULT_BG, draw);
    G_Main(&g);
    G_Destroy(&g);
    return 0;
}