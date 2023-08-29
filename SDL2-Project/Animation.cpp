#include "Animation.h"

#include <stdexcept>

#include "SDL2Common.h"


/**
 * Animation
 * 
 * Animation default constructor 
 * 
 * @return Constructed object  
 */
Animation::Animation()
{
    // Should be set by init - use frames
    // to check for init not being called. 
    maxFrames = 0;
    frames = nullptr;

    // Need to be able to set this!
    frameTimeMax = 0.4f; // Default to 24fps

    //set current animation frame to first frame. 
    currentFrame = 0;

    //zero frame time accumulator
    accumulator = 0.0f;

    // most of our animations loop so
    loop = true;
}

/**
 * init
 * 
 * Method to populate an animation structure from given paramters. 
 * 
 * @param noOfFrames Frames of animation
 * @param SPRITE_WIDTH Width of the sprite
 * @param SPRITE_HEIGHT Height of the sprite
 * @param row Row of the grid to take the sprites from or -1 if working along a row. 
 * @param col Column of the grid to take the sprites from or -1 if along a column.
 * @exception Throws a runtime error if rows/cols are malformed.  
 */
void Animation::init(int noOfFrames, 
                              const int SPRITE_WIDTH, const int SPRITE_HEIGHT, 
                              int rows, int cols)
{
    // set frame count.
    maxFrames = noOfFrames;

    // allocate frame array
    frames = new SDL_Rect[maxFrames]; 

    int i = 0;
     //Setup animation frames - fixed row!
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (i >= maxFrames) {
                break;
            }
            frames[i].x = SPRITE_WIDTH * col;
            frames[i].y = SPRITE_HEIGHT * row;
            frames[i].w = SPRITE_WIDTH;
            frames[i].h = SPRITE_HEIGHT;
            i++;
        }
    }

}

/**
 * ~Animation
 * 
 * Destructor cleans up an animation object.  
 * 
 */
Animation::~Animation()
{
    //Free the memory - we allocated it with new
    // so must use the matching delete operation.
    delete [] frames;

    // Good practice to set pointers to null after deleting
    // ths prevents accidental access. 
    frames = nullptr;
}

/**
 * getCurrentFrame
 * 
 * Get the current frame for rendering
 * @return Pointer to the current frame of animation. 
 * 
 */
SDL_Rect* Animation::getCurrentFrame()
{
    return &frames[currentFrame];
}

/**
 * update
 * 
 * Use time to update current frame
 * @param timeDeltaInSeconds the time delta in seconds
 * 
 */
void Animation::update(float timeDeltaInSeconds)
{
     // Add elapsed time to the animation accumulator. 
    accumulator += timeDeltaInSeconds;

    // Check if animation needs update
    if(accumulator > frameTimeMax)
    {
        accumulator = 0.0f;

        // Note, only increment if you have
        // another frame to go. 
        if(currentFrame < maxFrames-1)
            currentFrame++;
        else   
        {
            if(loop == true)
                currentFrame = 0;
            
            // if animation is not re-set
            // stays on maxFrames -1
        }
    }
}

void Animation::setMaxFrameTime(float max)
{
    frameTimeMax = max;
}

void Animation::setLoop(bool loop)
{
    this->loop = loop;
}