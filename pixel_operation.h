/*Prototype for pixel_operation*/
#ifndef PIXEL_H
#define PIXEL_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL/SDL_image.h>

typedef enum {NOTHING,WORKING} state_type;
SDL_Surface *screen, *image;
int height,weight;

int isSDLWorking();
int setScreenSize(int height,int weight);
SDL_Surface* loadImage(SDL_Surface *image,char *image_name);
Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);
void update_Screen(SDL_Surface *image);
void putpixel(SDL_Surface *Surface, unsigned x, unsigned y, Uint32 pixel);
SDL_Surface* greyscale(SDL_Surface *img);
SDL_Surface* blackWhite(SDL_Surface *img);
Uint32 getPixelSum(SDL_Surface *img,int x,int y);
SDL_Surface* getPixelSumIt(SDL_Surface *img);
SDL_Surface* setIntegralImage(SDL_Surface *img);
int pixelImageIntegral(SDL_Surface *img, int x, int y);
int s(SDL_Surface *img,int x, int y);
SDL_Surface* GetIntegralImage(SDL_Surface *img, unsigned int **matrix);
unsigned int** IntegralImage(SDL_Surface *img);
SDL_Surface* TrueIntegralImage(SDL_Surface *img);
unsigned int getColSum(unsigned int **matrix, int i, int j);
unsigned int getRowSum(unsigned int **matrix, int i, int j);
unsigned int** build_matrix(int dimW,int dimH);
void print_dynmat(unsigned int **mat, int dimW,int dimH);
//SDL_Surface* display_image(SDL_Surface *img);
#endif /*PIXEL_H*/
