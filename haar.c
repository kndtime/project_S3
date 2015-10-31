#include "haar.h"
#include <SDL/SDL_image.h>

void haar_features_a(SDL_Surface *img){
  int feature = 0;
  int *vector = 0;
  int h = img->h;
  int w = img->w;
  for(int i = 0; i<h ; i++)
    {
      for(int j = 0; j<w ; j++)
	{
	  for(int h1 = 1 ; i+h1-1<= h; h1++)
	    {
	      for(int w1 = 1 ; j+2*w1-1<= w; w1++)
		{
	          Uint32 p = getpixel(img,(unsigned)i,(unsigned)j);
	          Uint32 p1 = getpixel(img,(unsigned)i+1,(unsigned)j);
	          vector[feature]= p-p1;
		  vector++;
		  printf("%i\n",vector[feature]);
	          feature++;
		}
	    }
	}
    }
}
/*
void haar_features_b(SDL_Surface *img){
  int feature = 0;
  int *vector;
  int h = img->h;
  int w = img->w;
  int j = 1;
  for(int i = 1; i<=h && j <= w ; i++)
    {
      int 
      while(i+h-1 <= h && j+2w-1)
    }
    }*/
