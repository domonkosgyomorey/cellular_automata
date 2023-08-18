#ifndef ELEMENTARY_CA_H
#define ELEMENTARY_CA_H

#include <SDL2/SDL.h>

typedef enum {
  CA_DEATH = 0,
  CA_ALIVE
} E_CA_cell;

typedef struct {
  int w, h, cl;
  E_CA_cell* board;
} E_CA_board;

E_CA_board* init_e_ca_board(int w, int h, const char ca_rule[8]);
void e_ca_update_board(E_CA_board* board_ptr);
void e_ca_render(SDL_Renderer* renderer, E_CA_board* board, int ww, int wh);

#endif // ELEMENTARY_CA_H
