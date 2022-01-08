#include "SDL2/SDL.h"

#include "game.h"
#include "graphics.h"

void Game_Init(Game *game, DrawFunc draw) {
    game->player = &(Player){
        .pos = &(Point2){0, 0}
    };
    game->draw = draw;
}

void Game_HandleKeyDown(Game *game, SDL_KeyboardEvent *k) {
    int code;
    if (0 < (code = k->keysym.scancode) && code < 128) {
        switch (code) {
            default:
                break;
        }
    }
    printf("Key press detected: %d ['%c']\n", code, code);
}

// the main function
void Game_Main(Game *game) {
    G_Init(game->graphics, DEFAULT_BG);

    SDL_Event event;
    bool crashed = false;
    while(!crashed) {
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_KEYDOWN:
                    Game_HandleKeyDown(game, &event.key);
                    break;
                case SDL_QUIT:
                    crashed = true;
                    break;
            }
        }
        SDL_Delay(32);
        game->draw(game);
    }

    G_Destroy(game->graphics);
}