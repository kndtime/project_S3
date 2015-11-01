#include "haar.h"
#include <SDL/SDL_image.h>

unsigned long haar_rect(int x,int y , int h , int w,unsigned int **matrix){
  return ((matrix[x-1][y-1]+matrix[x+h-1][y+w-1])-(matrix[x-1][y+w-1]+matrix[x+h-1][y-1]));
  /*Somme de A+D-(B+C) dans un rectangle , A correspond au côté en haut à gauche,D le côté en bas à droite,B le côté en haut à droite et C en bas à gauche*/
}

int haar_features_a(int x,int y,int h,int w,unsigned int **matrix){
    unsigned int white = haar_rect(x,y+w/2,h,w/2,matrix);
    unsigned int black = haar_rect(x,y,h,w/2,matrix);
    return white-black;
    /*2 rectangles horizontaux*/
}


int haar_features_b(int x,int y,int h,int w,unsigned int **matrix){
  unsigned int white = haar_rect(x+h/2,y,h/2,w,matrix);
  unsigned int black = haar_rect(x,y,h/2,w,matrix);
  return white-black;
  /* 2 rectangles verticaux*/
}  

int haar_features_c(int x,int y,int h,int w,unsigned int **matrix){
    unsigned int white = haar_rect(x,y,h,w/3,matrix)+haar_rect(x,y+2*w/3,h,w/3,matrix);
    unsigned int black = haar_rect(x,y+w/3,h,w/3,matrix);
    return white-black;
    /*3 rectangles horizontaux*/
}

  int haar_features_d(int x,int y,int h,int w,unsigned int **matrix){
    unsigned int white = haar_rect(x,y,h/3,w,matrix)+haar_rect(x+2*h/3,y,h/3,w,matrix);
    unsigned int black = haar_rect(x+h/3,y,h/3,w,matrix);
    return white-black;
    /*3 rectangles verticaux*/
  }

  int haar_features_e(int x ,int y,int h,int w,unsigned int **matrix){
    unsigned int white = haar_rect(x,y,h/2,w/2,matrix)+haar_rect(x+h,y+w,h/2,w/2,matrix);
    unsigned int black = haar_rect(x+h/2,y,h/2,w/2,matrix)+haar_rect(x,y+w/2,h/2,w/2,matrix);
    return white-black;
    /*4 rectangles*/
  }

  void use_haar()
