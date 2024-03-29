#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <stdbool.h>

#include "SDL2/SDL.h"

#define debug printf("L%d\n", __LINE__)

#define DEFAULT_SCREEN_PERCENT_W 60.0 / 100.0
#define DEFAULT_SCREEN_PERCENT_H 60.0 / 100.0

#define GRIDSIZE 200

typedef struct {
    int x, y;
} Point2;

void P2_Print(Point2 *p);

typedef struct {
    int w, h;
} Size2;

typedef struct {
    Uint8 r, g, b, a;
} Color4;

typedef struct {
    int x, y, w, h;
} Rect;

typedef enum { Corner, Center } RectMode;


typedef struct {
    SDL_Window *win;
    SDL_Renderer *ren;
    Color4 *bg_color;
} Graphics;


int G_Init(Graphics *g, Color4 *bg);
void G_Update(Graphics *g);
void G_Destroy(Graphics *g);

Size2 G_WinSize(Graphics *g);

void G_SetColor(Graphics *g, Color4 *c);
void G_FillBG(Graphics *g, Color4 *c);
void G_DrawLine(Graphics *g, Point2 *start, Point2 *end, Color4 *c);
void G_DrawGrid(Graphics *g, int gridsize, Point2 *center, Color4 *c);
void G_DrawRect(Graphics *g, Rect *r, Color4 *c, RectMode mode, bool fill);

#endif // _GRAPHICS_H