#include "haar.h"
#include <SDL/SDL_image.h>

//static double F= 0.5;
//static double d = 0.995;
static double Ftarget =0.8;
static int nStages = 12;
static int framesize;
int features=5;


unsigned long haar_rect(int x,int y , int h , int w,unsigned int **matrix){
  return ((matrix[x-1][y-1]+matrix[x+h-1][y+w-1])-(matrix[x-1][y+w-1]+matrix[x+h-1][y-1]));
  /*Somme de A+D-(B+C) dans un rectangle , A correspond au côté en haut à gauche,D le côté 
  en bas à droite,B le côté en haut à droite et C en bas à gauche*/
}

int haar1(int x,int y,int h,int w,unsigned int **matrix){
    unsigned int white = haar_rect(x,y+w/2,h,w/2,matrix);
    unsigned int black = haar_rect(x,y,h,w/2,matrix);
    return white-black;
    /*2 rectangles horizontaux*/
}


int haar2(int x,int y,int h,int w,unsigned int **matrix){
  unsigned int white = haar_rect(x+h/2,y,h/2,w,matrix);
  unsigned int black = haar_rect(x,y,h/2,w,matrix);
  return white-black;
  /* 2 rectangles verticaux*/
}  

int haar3(int x,int y,int h,int w,unsigned int **matrix){
    unsigned int white = haar_rect(x,y,h,w/3,matrix)+haar_rect(x,y+2*w/3,h,w/3,matrix);
    unsigned int black = haar_rect(x,y+w/3,h,w/3,matrix);
    return white-black;
    /*3 rectangles horizontaux*/
}

  int haar4(int x,int y,int h,int w,unsigned int **matrix){
    unsigned int white = haar_rect(x,y,h/3,w,matrix)+haar_rect(x+2*h/3,y,h/3,w,matrix);
    unsigned int black = haar_rect(x+h/3,y,h/3,w,matrix);
    return white-black;
    /*3 rectangles verticaux*/
  }

  int haar5(int x ,int y,int h,int w,unsigned int **matrix){
    unsigned int white = haar_rect(x,y,h/2,w/2,matrix)+haar_rect(x+h,y+w,h/2,w/2,matrix);
    unsigned int black = haar_rect(x+h/2,y,h/2,w/2,matrix)+haar_rect(x,y+w/2,h/2,w/2,matrix);
    return white-black;
    /*4 rectangles*/
  }

  void use_haar(SDL_Surface *img,unsigned int **matrix){
    for (int i = 0; i < img->w ; ++i)
    {
      for (int j = 0; j < img->h; ++j)
      {
        for (int x = 0; x < i-framesize; ++x)
        {
          for (int y = 0; y < j -framesize; ++y)
          {
            matrix[i][j]+= haar1(x,y,i,j,matrix)
            +haar2(x,y,i,j,matrix)
            +haar3(x,y,i,j,matrix)
            +haar4(x,y,i,j,matrix)
            +haar5(x,y,i,j,matrix);
          }
        }
      }
    }
  }

  long *MoveFeatures(int frameSize,unsigned int **tab){
    long* res = malloc(162336*sizeof(long));
    int feature[5][2] = {{2,1}, {1,2}, {3,1}, {1,3}, {2,2}};
    int c = 0;
    for (int i = 0; i < 5; i++){
      int X = feature[i][0];
      int Y = feature[i][1];
      for (int x = 0; x <= frameSize-X; x++){
        for (int y = 0; y <= frameSize-Y; y++){
          for (int w = X; w <= frameSize-x; w+=X){
            for (int h = Y; h <= frameSize-y; h+=Y){
              if (i==0)
                res[c] = haar1(x,y,h,w,tab);
              if (i==1)
                res[c] = haar2(x,y,h,w,tab);
              if (i==2)
                res[c] = haar3(x,y,h,w,tab);
              if (i==3)
                res[c] = haar4(x,y,h,w,tab);
              if (i==4)
                res[c] = haar5(x,y,h,w,tab);
              c++;
          }
        }
      }
    }
  }
  return res;  
}

  //Adaboost
  void CascadeFeature(){
    double *m = 0,*n = 0;
    // False alarm rate of the cascade with i stages
    double Fi = 1;
    int i = 0;
    while(Fi > Ftarget && i < nStages)
    {
      i++;
      initWeight(m,n);
    }
  }

  void initWeight(double *m, double *n)
  {
    *m = (double) 0.5 / *m;
    *n = (double) 0.5 / *n;
    *m =  (*m - getPositiveThreshold());
    *n =  (*n - getNegativeThreshold());
  }

  double getNegativeThreshold()
  {
    return 3000.045;
  }
  double getPositiveThreshold()
  {
    return 5000.045;
  }
