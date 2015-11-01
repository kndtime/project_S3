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
int haar_features_a(int x,int y,int h,int w,unsigned int **matrix);
int haar_features_b(int x,int y,int h,int w,unsigned int **matrix);
int haar_features_c(int x,int y,int h,int w,unsigned int **matrix);
int haar_features_d(int x,int y,int h,int w,unsigned int **matrix);
int haar_features_e(int x,int y,int h,int w,unsigned int **matrix);
void use_haar(SDL_Surface *img,unsigned int **matrix); /*à faire*/
void CascadeFeature();
double getNegativeThreshold();
double getPositiveThreshold();
void initWeight(double *m, double *n);
#endif /* HAAR_H */
