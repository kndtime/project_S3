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


int haar_features_a(int x,int y,int w ,unsigned int **matrix);
int haar_features_b(int x,int y,int w ,unsigned int **matrix);
int haar_features_c(int x,int y,int w ,unsigned int **matrix);
int haar_features_d(int x,int y,int w ,unsigned int **matrix);
int haar_features_e(int x,int y,int w ,unsigned int **matrix);
int use_haar(); /*à faire*/

#endif /* HAAR_H */
