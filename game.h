#ifndef _GAME_H
#define _GAME_H

#include "SDL2/SDL.h"

#include "graphics.h"

#define DEFAULT_BG &(Color4){140, 140, 140, 255}
typedef struct {
    Point2 *pos;
} Player;

// do NOT fuck with the next 10 lines
struct game;

typedef void (*DrawFunc)(struct game *);

typedef struct game {
    Player *player;
    Graphics *graphics;
    DrawFunc draw; // should run once every frame
} Game;

void Game_Init(Game *game);
void Game_Main(Game *game);

void update_graphics(Game *game);

#endif // _GAME_H