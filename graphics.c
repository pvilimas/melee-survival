#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "SDL2/SDL.h"

#include "graphics.h"

void P2_Print(Point2 *p) {
    printf("Point(%d, %d)\n", p->x, p->y);
}

int G_Init(Graphics *g, Color4 *bg) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    // init
    if (SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "SDL failed to initialize: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // get screen dimensions
    SDL_DisplayMode dispmode;
    SDL_GetCurrentDisplayMode(0, &dispmode);

    // starting dimensions
    int win_w = dispmode.w * DEFAULT_SCREEN_PERCENT_W,
        win_h = dispmode.h * DEFAULT_SCREEN_PERCENT_H;
    // printf("screen size: (%d, %d)\n", dispmode->w, dispmode->h);
    // printf("starting dim: (%d, %d)\n", win_w, win_h);

    window = SDL_CreateWindow(
        "Melee Survival",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        win_w, win_h,
        0
    );
    if (!window) {
        fprintf(stderr, "SDL window error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE); 
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "SDL renderer error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE); 
    }


    g->win = window;
    g->ren = renderer;
    g->bg_color = bg;
    
    return EXIT_SUCCESS;
}

Size2 G_WinSize(Graphics *g) {
    int w, h;
    SDL_GetWindowSize(g->win, &w, &h);
    return (Size2){w, h};
}

void G_Update(Graphics *g) {
    SDL_RenderPresent(g->ren);
    SDL_UpdateWindowSurface(g->win);
}

// if color is null, reset to default
void G_SetColor(Graphics *g, Color4 *c) {
    (c != NULL)
        ? SDL_SetRenderDrawColor(g->ren, c->r, c->g, c->b, c->a)
        : SDL_SetRenderDrawColor(g->ren, g->bg_color->r, g->bg_color->g, g->bg_color->b, g->bg_color->a);
}

// if color is null, use default
void G_FillBG(Graphics *g, Color4 *c) {
    (c != NULL)
        ? SDL_SetRenderDrawColor(g->ren, c->r, c->g, c->b, c->a)
        : SDL_SetRenderDrawColor(g->ren, g->bg_color->r, g->bg_color->g, g->bg_color->b, g->bg_color->a);
    SDL_RenderClear(g->ren);
}

// if color is null, ignore and use previous color
void G_DrawLine(Graphics *g, Point2 *start, Point2 *end, Color4 *c) {
    if (c != NULL)
        SDL_SetRenderDrawColor(g->ren, c->r, c->g, c->b, c->a);
    SDL_RenderDrawLine(g->ren, start->x, start->y, end->x, end->y);
}

// if color is null, ignore and use previous color
// TODO: add rectmode arg
void G_DrawGrid(Graphics *g, int gridsize, Point2 *center, Color4 *c) {
    if (c != NULL)
        SDL_SetRenderDrawColor(g->ren, c->r, c->g, c->b, c->a);

    Point2 offset = {(G_WinSize(g).w / 2) - center->x, (G_WinSize(g).h / 2) - center->y};
    
    // P2_Print(&offset);

    Size2 winsize = G_WinSize(g);
    int num_horiz = (int) ceil(winsize.w / gridsize),
        num_vert = (int) ceil(winsize.h / gridsize);
    Point2 margin_topleft = {
        -(winsize.w / 2) - gridsize,
        -(winsize.h / 2) - gridsize,
    },
    margin_botright = {
        (winsize.w / 2) + gridsize,
        (winsize.h / 2) + gridsize
    };

    // draw horizontal lines
    for (int i = 0; i < num_horiz; i++){
        G_DrawLine(g, 
            &(Point2){offset.x + i * gridsize, offset.y + margin_topleft.y},
            &(Point2){offset.x + i * gridsize, offset.y + margin_botright.y},
            NULL
        );
        G_DrawLine(g, 
            &(Point2){offset.x - i * gridsize, offset.y - margin_topleft.y},
            &(Point2){offset.x - i * gridsize, offset.y - margin_botright.y},
            NULL
        );
    }

    // draw vertical lines
    for (int i = 0; i < num_vert; i++){
        G_DrawLine(g, 
            &(Point2){offset.x + margin_topleft.x, offset.y + i * gridsize},
            &(Point2){offset.x + margin_botright.x, offset.y + i * gridsize},
            NULL
        );
        G_DrawLine(g, 
            &(Point2){offset.x - margin_topleft.x, offset.y - i * gridsize},
            &(Point2){offset.x - margin_botright.x, offset.y - i * gridsize},
            NULL
        );
    }

}
// if color is null, ignore and use previous color
void G_DrawRect(Graphics *g, Rect *r, Color4 *c, RectMode mode, bool fill) {
    if (c != NULL)
        SDL_SetRenderDrawColor(g->ren, c->r, c->g, c->b, c->a);
    int abs_x, abs_y;
    if (mode == Center) {
        // x, y => x-w/2, y-h/2
        abs_x = r->x - (r->w / 2);
        abs_y = r->y - (r->h / 2);
    } else if (mode == /* top left */ Corner) {
        // x, y => x, y
        abs_x = r->x;
        abs_y = r->y;
    } else {
        assert(0 && "Unreachable code");
    }

    SDL_Rect *draw_rect = &(SDL_Rect){abs_x, abs_y, r->w, r->h};
    if (fill)
        SDL_RenderFillRect(g->ren, draw_rect);

    SDL_RenderDrawRect(g->ren, draw_rect);
}

void G_Destroy(Graphics *g) {
    SDL_DestroyWindow(g->win);
    SDL_DestroyRenderer(g->ren);
    SDL_Quit();
}