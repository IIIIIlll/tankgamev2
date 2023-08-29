/*
  Moving Game into it's own structure / files.  
*/

//For exit()
#include <cstdlib>

//for printf
#include <cstdio>

#include "SDL2Common.h"
#include "Game.h"

const int SDL_OK = 0;

int main( int argc, char* args[] )
{
    // SDL allows us to choose which SDL components are going to be
    // initialised. We'll go for everything for now!
    int sdl_status = SDL_Init(SDL_INIT_EVERYTHING);

    if(sdl_status != SDL_OK)
    {
        //SDL did not initialise, report and error and exit. 
        printf("Error -  SDL Initialisation Failed\n");
        exit(1);
    }

    Game *game = new Game();

    game->init();

    game->runGameLoop();
    
    delete game;

    //Shutdown SDL - clear up resources etc.
    SDL_Quit();

    exit(0);
}





