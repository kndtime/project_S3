/*Pixel_operation.c
 * is mainly for pre processing algorithms*/
#include "pixel_operation.h"

int **matrix;

int isSDLWorking(){
if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
          fprintf(stderr, "SDL INIT FAILURE\n");
              return 1;
                }
  printf("SDL INIT SUCCESS\n");
  return 0;
}

int setScreenSize(int height, int weight){
screen = SDL_SetVideoMode(height, weight, 0, SDL_ANYFORMAT);
  if ( screen == NULL ) {
            fprintf(stderr,
                "Echec de creation de la fenetre de 160*160 : %s.\n"
                , SDL_GetError());
                return 1;}
return 0;
}

SDL_Surface* loadImage(SDL_Surface *image,char *image_name){
  image = IMG_Load(image_name);
    if ( image == NULL ){
              fprintf(stderr,
                  "Echec de chargement du fichier image.bmp : %s.\n",
                  SDL_GetError());
                  return NULL;}
    else{
      /*Apply the image on the screen*/
    SDL_BlitSurface(image, NULL, screen, NULL);
    /*Update the screen with the image*/
    SDL_UpdateRect(screen, 0, 0, 0, 0);
    }
  return image;
}

void update_Screen(SDL_Surface *image){
    /*Apply the image on the screen*/
    SDL_BlitSurface(image, NULL, screen, NULL);
    /*Update the screen with the image*/
    SDL_UpdateRect(screen, 0, 0, 0, 0); 
}

static inline
Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y) {
  int bpp = surf->format->BytesPerPixel;
  return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
}

Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y) {
  Uint8 *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel) {
  case 1:
    return *p;
  case 2:
    return *(Uint16 *)p;
  case 3:
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
      return p[0] << 16 | p[1] << 8 | p[2];
    else
      return p[0] | p[1] << 8 | p[2] << 16;
  case 4:
    return *(Uint32 *)p;
  }
  return 0;
}

void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel) {
  Uint8 *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel) {
  case 1:
    *p = pixel;
    break;
  case 2:
    *(Uint16 *)p = pixel;
    break;
  case 3:
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
      p[0] = (pixel >> 16) & 0xff;
      p[1] = (pixel >> 8) & 0xff;
      p[2] = pixel & 0xff;
    } else {
      p[0] = pixel & 0xff;
      p[1] = (pixel >> 8) & 0xff;
      p[2] = (pixel >> 16) & 0xff;
    }
    break;
  case 4:
    *(Uint32 *)p = pixel;
    break;
  }
}

/*int greyscale(SDL_Surface *img){
  for (int i = 0; i < img->h; i++) {
    for (int j = 0; j < img->w; j++) {
      Uint32 p = getpixel(img,i,j);
      Uint8 r = p >> 16 & 0xFF;
      Uint8 g = p >> 8 & 0xFF;
      Uint8 b = p & 0xFF;
      Uint8 v = 0.212671f * r
                            + 0.715160f * g
                            + 0.072169f * b;
      //p = (0xFF << 24) | (v << 16) | (v << 8) | v;
      putpixel(img,i,j,v);
    }
  }
  return 0;
}*/

SDL_Surface* greyscale(SDL_Surface *img){
      Uint8 r,g,b;
      //Uint32 grey = 0;
      if (img!=NULL)
      {
        for (int i = 0; i <= img->h; i++) {
          for (int j = 0; j <= img->w; j++) {
            Uint32 p = getpixel(img,i,j);
            SDL_GetRGB(p, img->format, &r,&g,&b);
            //Uint32 v = 0.212671f * r + 0.715160f * g + 0.072169f * b; 
            Uint32 v = r+g+b/3;         
            putpixel(img,i,j,SDL_MapRGB(img->format,v,v,v));
    }
  }
      }else{
        return NULL;
  }
  return img;
}

SDL_Surface* blackWhite(SDL_Surface *img){
  Uint8 r,g,b;
  for (int i = 0; i <= img->h; i++){
    for (int j = 0; j < img->w; j++){
      Uint32 p = getpixel(img,i,j);
      SDL_GetRGB(p, img->format, &r,&g,&b);
      if (r+g+b<(255/2))
      {
        putpixel(img,i,j,SDL_MapRGB(img->format,0,0,0));
      }
      else{
        putpixel(img,i,j,SDL_MapRGB(img->format,255,255,255));
      }
    }
  }
  return img;
}
//Recursive
Uint32 getPixelSum(SDL_Surface *img,int x,int y){
  //Uint8 r,g,b;
  if ((img->h<x || img->h<y) || (x<0 || y<0) )
  {
    return 0;
  }
  Uint32 p = getpixel(img,x,y) + getPixelSum(img,x-1,y)+getPixelSum(img,x,y-1)- getPixelSum(img,x-1,y-1);
  //SDL_GetRGB(p, img->format, &r,&g,&b);
  putpixel(img,x,y,p);
  return p;
}
//Iterative
SDL_Surface* getPixelSumIt(SDL_Surface *img){
  Uint8 r,g,b;
  Uint32 sum;
  for (int i = 0; i < img->h ; ++i)
  {
    for (int j = 0; j  < img->w; ++j)
    {
      for (int m = i; m > 0; --m)
      {
        sum = 0;
        for (int n = j; n > 0; --n)
        {
          sum += getpixel(img,m,n);
          printf("%i\n", sum );
        }
      }
      SDL_GetRGB(sum, img->format, &r,&g,&b);
      putpixel(img,i,j,SDL_MapRGB(img->format,r,g,b));
    }
  }
  return img;
}

SDL_Surface* setIntegralImage(SDL_Surface *img){
 Uint32 p = 0;
    for (int i = 0; i < img->h; ++i)
    {
      for (int j = 0; j < img->w; ++j)
      {
	p = pixelImageIntegral(img,i,j);
        putpixel(img,i,j,SDL_MapRGB(img->format,p,p,p));
      }
    }
    return img;
  }

  int pixelImageIntegral(SDL_Surface *img, int x, int y){

    int p =  getpixel(img,x,y) + s(img,x-1,y)+ s(img,x,y-1) - s(img,x-1,y-1);
    //printf("%i\n", p );
    if (p<0)
    {
      return 0;
    }
    return p;
  }

  int s(SDL_Surface *img,int x, int y){
    int sum = 0;
    for (int i = x; i > 0 ;--i)
    {
      for (int j = y; j > 0; --j)
      {
        sum += getpixel(img,i,j);
      }
    }
    return sum;
  }

unsigned int** IntegralImage(SDL_Surface *img){
  int x,y;
  unsigned int **tab =NULL;
  tab[1][1] = getpixel(img,0,0);
  for(x=2;x < (img->h+1); x++)
  {
    tab[x][1] = tab[x-1][1] + getpixel(img , x-1,0);
  }
  for(y=2 ; y < img -> w+1 ; y++){
    unsigned int line = getpixel(img,0,y-1);
    tab[1][y]= tab[1][y-1] + line;
    line = 0;
    for(x=1;x<img->h+1;x++){
     line += getpixel(img,x-1,y-1);
     tab[x][y] = tab [x][y-1] + line;
    }
  }
  return tab;
}

 SDL_Surface* GetIntegralImage(SDL_Surface *img, unsigned int **matrix)
 {
   for (int i = 0; i < img->w; ++i)
   {
     for (int j = 0; i < img->h; ++i)
     {
       putpixel(img,i,j,matrix[i][j]);
     }
    }
    return img;
 }

SDL_Surface* TrueIntegralImage(SDL_Surface *img)
{
  // Allocate S and ii matrices.
    //unsigned int matrix[img->w][img->h];
    unsigned int **matrix = build_matrix(img->w,img->h);
    for (int i = 0; i < img->w; ++i)
    {
      for (int j = 0; j < img->h; ++j)
      {
        matrix[i][j] = getpixel(img,i,j); 
      }
    }

    print_dynmat(matrix,img->w,img->h);

    for (int j = 0; j < img->w; ++j){
      for(int i = 1; i < img->h; ++i) {
        matrix[i][j] = getColSum(matrix,i,j)+
        getColSum(matrix,i-1,j);
      }
    }

    for (int j = 0; j < img->w; ++j){
      for(int i = 1; i < img->h; ++i) {
        matrix[j][i] = getRowSum(matrix,i,j)+
        getRowSum(matrix,i,j-1);
      }
    }
    if(!matrix) { 
        printf("%s\n", "WARNING: Integral image is null." );
        return img;
    }

    for (int i = 0; i < img->w; ++i)
    {
      for (int j = 0; j < img->h; ++j)
      {
         putpixel(img,i,j,matrix[i][j]);
      }
    }
    return img;
}

unsigned int** build_matrix(int dimW,int dimH) {
  unsigned int         **mat;
  mat = malloc(dimW * sizeof (int *));
  for (int i = 0; i < dimH; ++i)
    mat[i] = malloc(dimH * sizeof (int));
  return mat;
}

void print_dynmat(unsigned int **mat, int dimW,int dimH) {
  for (int i = 0; i < dimW; ++i) {
    for (int j = 0; j < dimH; ++j)
      printf("%02d ", mat[i][j]);
    printf("\n");
  }
}


unsigned int getColSum(unsigned int **matrix, int i, int j){
  unsigned int count = 0;
  for (int h = i; h > 0; --h)
  {
    count += matrix[h][j];
  }
  return count;
}

unsigned int getRowSum(unsigned int **matrix, int i, int j){
  unsigned int count = 0;
  for (int h = j; h > 0; --h)
  {
    count += matrix[h][i];
  }
  return count;
}


