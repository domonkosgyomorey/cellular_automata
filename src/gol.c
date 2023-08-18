#include "gol.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <time.h>

Gol_board* gol_init_board(int width, int height){
  Gol_board* board_ptr = (Gol_board*)malloc(sizeof(Gol_board));
  board_ptr->w = width;
  board_ptr->h = height;

  srand(time(0));

  board_ptr->board = (Gol_cell*)malloc(sizeof(Gol_cell)*width*height);
  for (int i = 0; i < height*width; ++i) {
      board_ptr->board[i] = (Gol_cell)(rand()%2);
  }
  return board_ptr;
}

void gol_update_board(Gol_board* board_ptr){
  int width = board_ptr->w;
  int height = board_ptr->h;
  Gol_cell* board = board_ptr->board;
  
  Gol_cell tmp_board[height*width];

  for (int i = 0;i < board_ptr->h; ++i) {
    for (int j = 0; j < board_ptr->w; ++j) {
      char count = 0;
      for(int ii = -1; ii < 2; ++ii){
        for(int jj = -1; jj < 2; ++jj){
          if(i+ii>=0&&i+ii<height&&j+jj>=0&&j+jj<width){
            count+=((ii||jj)&&board[(i+ii)*width+(j+jj)]==ALIVE);
          }
        }
      }
      if(count==3 || (count==2&&board[i*width+j]==ALIVE)){
        tmp_board[i*width+j] = ALIVE;
      }else{
        tmp_board[i*width+j] = DEATH;
      }
    }
  }
  memcpy(board, tmp_board, sizeof(Gol_cell)*width*height);
}

void gol_render(SDL_Renderer* renderer, Gol_board* board_ptr, int ww, int wh){
  int width = board_ptr->w;
  int height = board_ptr->h;
  int pxw = ww/width;
  int pxh = wh/height;
  Gol_cell* board = board_ptr->board;
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      SDL_Rect rect = (SDL_Rect){j*pxw, i*pxh, pxw, pxh};
      int col = board[i*width+j];
      SDL_SetRenderDrawColor(renderer, col*255, col*255, col*255, 255);
      SDL_RenderDrawRect(renderer, &rect);
    }
  }
}

