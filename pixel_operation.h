/*Prototype for pixel_operation*/
#ifndef PIXEL_H
#define PIXEL_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

typedef enum {NOTHING,WORKING} state_type;
SDL_Surface *screen, *image;
int height,weight;

int isSDLWorking();
int setScreenSize(int height,int weight);
int loadImage(SDL_Surface *image,char *image_name);
Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
int greyscale(SDL_Surface *img);
//SDL_Surface* display_image(SDL_Surface *img);
#endif /*PIXEL_H*/
