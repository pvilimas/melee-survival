#include "game.h"
#include "graphics.h"

void Game_Init(Game *game) {
    game->player = &(Player){
        .pos = &(Point2){0, 0}
    };
}

// the main function
void Game_Main(Game *game) {
    
    G_Init(game->graphics, DEFAULT_BG);

    SDL_Event event;
    bool crashed = false;
    while(!crashed) {
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    crashed = true;
                    break;
            }
        }
        SDL_Delay(32);
    }
    game->draw(game);

    G_Destroy(game->graphics);
}