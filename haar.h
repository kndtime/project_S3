#ifndef HAAR
# define HAAR

# include <stdlib.h>
# include <string.h>

typedef struct
{
  char *color;
  int , *x, *y;

}Haar;

Haar *init_car(char *color);
char *get_color();

#endif /* HAAR_H */
