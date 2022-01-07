#ifndef _GAME_H
#define _GAME_H

#include "SDL2/SDL.h"

#include "graphics.h"

typedef struct {
    Point2 *pos;
} Player;

typedef struct {
    Player *player;
} Game;

void Game_Init(Game *game);
void Game_Main(Game *game);

void update_graphics(Graphics *g);

#endif // _GAME_H