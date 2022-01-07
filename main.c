#include <stdio.h>

#include "SDL2/SDL.h"

#include "game.h"
#include "graphics.h"

void update_graphics(Game *game) {
    Graphics *g = game->graphics;
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

int main(int argc, char *argv[]) {

    (void) argc;
    (void) argv;

    Game game;

    Game_Init(&game);
    Game_Main(&game);

}