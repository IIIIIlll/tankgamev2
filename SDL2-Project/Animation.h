#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "SDL2Common.h"

class Animation
{
private:
    int maxFrames;
    int currentFrame;

    float frameTimeMax;
    float accumulator;

    SDL_Rect *frames;

    bool loop;

public:
    Animation();
    ~Animation();

    // Throws exception!
    void init(int noOfFrames, 
                   const int SPRITE_WIDTH, const int SPRITE_HEIGHT, 
                   int row, int col);

    // Use time to update current frame 
    void update(float timeDeltaInSeconds);
    
    // Get the current frame for rendering
    SDL_Rect* getCurrentFrame();

    // Set max frametime
    void setMaxFrameTime(float max);

    // looping flag
    void setLoop(bool loop);  
};


#endif