#include "TextureUtils.h"

//for printf
#include <cstdio>

/**
 * Create Texture from File
 * 
 * Function to load a texture from a given filename and render context.
 * 
 * @param filename Filename of the file to load. 
 * @param renderer A pointer to the current SDL_Renderer. 
 * @return A pointer to the SDL_Texture created, or a nullptr on error. 
 */ 
SDL_Texture* createTextureFromFile(const char* filename, SDL_Renderer *renderer)
{
    // Texture which stores the actual sprite (this
    // will be optimised).
    SDL_Texture*     texture = nullptr;

    // Temporary surface used while loading the image
    SDL_Surface*     temp = nullptr;

    // Load the sprite to our temp surface
    temp = IMG_Load(filename);

    if(temp == nullptr)
    {
        printf("%s image not found!", filename);
    }    
    else  // Improved error handling, if we have no surface we can't make a texture.
    {
        // Create a texture object from the loaded image
        // - we need the renderer we're going to use to draw this as well!
        // - this provides information about the target format to aid optimisation.
        texture = SDL_CreateTextureFromSurface(renderer, temp);

        // Clean-up - we're done with 'image' now our texture has been created
        SDL_FreeSurface(temp);
        temp = nullptr;
    }

    return texture;
}
