#include "elementary_ca.h"
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

char rule[8] = {0, 1, 1, 1, 1, 0, 0, 0};

E_CA_board* init_e_ca_board(int w, int h, const char ca_rule[8]){
  E_CA_board* board_ptr = (E_CA_board*)malloc(sizeof(E_CA_board));
  board_ptr->w = w;
  board_ptr->h = h;
  board_ptr->cl = 1; 
  board_ptr->board = (E_CA_cell*)malloc(sizeof(E_CA_cell)*w*h);
  srand(time(0));
  for(int i = 0; i < w; ++i){
   // board_ptr->board[i] = (E_CA_cell)(rand()%2);
  }
  board_ptr->board[w/2] = CA_ALIVE;
  
  for(int i = 0; i < 8; ++i){
    rule[i] = ca_rule[i];
  }

  return board_ptr;
}

void e_ca_update_board(E_CA_board* board_ptr){
  int w = board_ptr->w;
  int h = board_ptr->h;
  int cl = board_ptr->cl;
  E_CA_cell* board = board_ptr->board;


#if 1
  for(int i = 0; i < w; ++i){
      int s = (board[(cl-1)*w+i]<<1);
      int f, t;
      if(i!=0){
        f = (board[(cl-1)*w+i-1]<<2); 
      }else{
        f = (board[cl*w-1]<<2);
      }
      if(i!=w-1){
        t =  (board[(cl-1)*w+i+1]);
      }else{
         t =  (board[(cl-1)*w+1]);
      }
      board[cl*w+i] = rule[f|s|t];
  }
  if(cl<h-1){
    board_ptr->cl++;
  }else{
    memcpy(board, board+w, sizeof(E_CA_cell)*w*h-w);
  }
#endif

#if 0
  if(cl<h-1){
     for(int i = 1; i < w-1; ++i){
      board[cl*w+i] = rule[(board[(cl-1)*w+i-1]<<2) | (board[(cl-1)*w+i]<<1) | (board[(cl-1)*w+i+1]<<0)];
  }
    board_ptr->cl++;
  }
#endif


}

void e_ca_render(SDL_Renderer* renderer, E_CA_board* board_ptr, int ww, int wh){
  int w = board_ptr->w;
  int h = board_ptr->h;
  E_CA_cell* board = board_ptr->board;
  int pxw = ww/w;
  int pxh = wh/h;
  for(int i = 0; i < h; ++i){
    for(int j = 0; j < w; ++j){
      SDL_Rect rect = (SDL_Rect){j*pxw, i*pxh, pxw, pxh};
      int col = board[i*w+j];
      SDL_SetRenderDrawColor(renderer, col*255, col*255, col*255, 255);
      SDL_RenderDrawRect(renderer, &rect);
    } 
  }
}

