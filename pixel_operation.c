/*Pixel_operation.c
 * is mainly for pre processing algorithms*/
#include "pixel_operation.h"


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
  image = SDL_LoadBMP(image_name);
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
            Uint32 v = 0.212671f * r + 0.715160f * g + 0.072169f * b;              
            putpixel(img,i,j,SDL_MapRGB(img->format,v,v,v) );
    }
  }
      }else{
        return NULL;
  }
  return img;
}

