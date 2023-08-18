#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "gol.h"
#include "elementary_ca.h"

Gol_board* board;
E_CA_board* ca_board;
int ww = 800, wh = 600;
int toggle_between_modes = 0;

int main(void){

  board = gol_init_board(800, 600);
  ca_board = init_e_ca_board(80, 60);

  if(SDL_Init(SDL_INIT_VIDEO)<0){
    printf("Error init sdl2\n");
    exit(1);
  }

  SDL_Window* window = SDL_CreateWindow("SDL window", 0, 0, ww, wh, 0);
  if(!window){
    printf("Error init sdl2 window\n");
    exit(1);
  }
  
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  
  if(!renderer){
    printf("Error init sdl2 renderer\n");
    exit(1);

  }

  SDL_Event event;
  while(1){
    while(SDL_PollEvent(&event)){
      switch(event.type){
        case SDL_QUIT:
          exit(0);
          break;
        case SDL_KEYDOWN:
          toggle_between_modes ^= 1;
          break;
        default:
          break;
      } 
    }
    SDL_SetRenderDrawColor(renderer, 0, 69, 169, 255);
    SDL_RenderClear(renderer);
    if(toggle_between_modes){
      gol_render(renderer, board, ww, wh);
      gol_update_board(board);
    }else{
      e_ca_render(renderer, ca_board, ww, wh);
      e_ca_update_board(ca_board);
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(16);
  }

  return 0;
}
