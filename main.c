#include <stdio.h>

#include "SDL2/SDL.h"

#include "game.h"
#include "graphics.h"

int main(int argc, char *argv[]) {

    (void) argc;
    (void) argv;

    Game game;

    Game_Init(&game);
    Game_Main(&game);

}