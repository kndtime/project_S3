// Includes:

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pixel_operation.h"

/*Variable Déclaration*/
int HEIGHT = 720;
int WEIGHT = 480;
SDL_Surface *image;
/*Function declaration*/
char* prompt_and_read(const char *prompt);
void wait_for_keypressed(void);
// Main function
int main()
{
	//Variables
	char *image_name;
  // Init SDL
  isSDLWorking();
  setScreenSize(HEIGHT,WEIGHT);
  image_name = prompt_and_read("Enter a filename : ");
  loadImage(image,image_name);
  //free(image_name);
  SDL_Delay(400);
  greyscale(image);
  void wait_for_keypressed();
  return 0;
}

char * prompt_and_read(const char * prompt) {
	  char * response;
	    char * bufsize;

		  printf("%s", prompt);
		    asprintf(&bufsize, "%%%us", BUFSIZ);

			  if((response = malloc(BUFSIZ + 1)) == NULL) {
				      fprintf(stderr,"out of memory\n");
					      exit(1);
						    }
			    scanf(bufsize, response);
				  free(bufsize);
				    return response;
}

void wait_for_keypressed(void) {
  SDL_Event             event;
  // Infinite loop, waiting for event
  for (;;) {
    // Take an event
    SDL_PollEvent( &event );
    // Switch on event type
    switch (event.type) {
    // Someone pressed a key -> leave the 
		case SDL_KEYDOWN: return;
    default: 
						  SDL_Delay(200);
						  break;
    }
  // Loop until we got the expected event
  }
}
