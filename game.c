#include "game.h"
#include "graphics.h"

#define DEFAULT_BG &(Color4){140, 140, 140, 255}

void update_graphics(Graphics *g) {
    // draw rect and lines
    G_SetColor(g, DEFAULT_BG);
    G_FillBG(g, NULL);
    G_DrawGrid(g, 200, &(Point2){100, 100}, &(Color4){0, 0, 0, 255});
    G_DrawRect(g, &(Rect){
        G_WinSize(g).w / 2, G_WinSize(g).h / 2,
        10, 10
    }, &(Color4){0, 0, 0, 255}, Center, true);
    G_Update(g);
}

void Game_Init(Game *game) {
    game->player = &(Player){
        .pos = &(Point2){0, 0}
    };
}

void Game_Main(Game *game) {

    Graphics g;

    G_Init(&g, DEFAULT_BG, update_graphics);
    G_Main(&g);
    G_Destroy(&g);
}