#ifndef HAAR
# define HAAR

# include <stdlib.h>
# include <string.h>
# include "pixel_operation.h"
typedef struct
{
  char *color;
  int  *x, *y;

}Haar;


unsigned long haar_rect(int x,int y , int h , int w,unsigned int **matrix);
int haar1(int x,int y,int h,int w,unsigned int **matrix);
int haar2(int x,int y,int h,int w,unsigned int **matrix);
int haar3(int x,int y,int h,int w,unsigned int **matrix);
int haar4(int x,int y,int h,int w,unsigned int **matrix);
int haar5(int x,int y,int h,int w,unsigned int **matrix);
void use_haar(SDL_Surface *img,unsigned int **matrix); /*à faire*/
long *MoveFeatures(int frameSize,unsigned int **tab);
void CascadeFeature();
double getNegativeThreshold();
double getPositiveThreshold();
void initWeight(double *m, double *n);
#endif /* HAAR_H */
