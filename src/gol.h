#ifndef GOL_H
#define GOL_H

#include <SDL2/SDL.h>

typedef enum {
  DEATH = 0,
  ALIVE,
} Gol_cell;

typedef struct {
  int w, h;
  Gol_cell* board;
} Gol_board;

Gol_board* gol_init_board(int width, int height);
void gol_update_board(Gol_board* board_ptr);
void gol_render(SDL_Renderer* renderer, Gol_board* board_ptr, int ww, int wh);

#endif // GOL_H
