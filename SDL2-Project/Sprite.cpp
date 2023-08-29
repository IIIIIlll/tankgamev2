#include "Sprite.h"
#include "Animation.h"
#include "Vector2f.h"
#include "TextureUtils.h"
#include "AABB.h"
#include "NPC.h"

#include <stdexcept>

/**
 * Sprite
 * 
 * Constructor, setup all the simple stuff. Set pointers to null etc. 
 *  
 */
Sprite::Sprite()
{
    speed = 50.0f;

    //Postion
    position = nullptr;

    //Velocity
    velocity = nullptr;

    // Set texture pointer
    texture = nullptr;
    
    // Animation array and size
    animations = nullptr;
    maxAnimations = 0;
    
    // Bounding box - can only 
    // be setup in derived class
    aabb = nullptr;
}

/**
 * initSprite
 * 
 * Function to populate an sprite structure from given paramters. 
 * 
 * @param renderer Target SDL_Renderer to use for optimisation.
 * @param maxAnimations total number of animations 
 * @param texturePath path to texture
 * @param position - initial position. 
 * @exception Throws an exception on file not found or out of memory. 
 */
void Sprite::init(SDL_Renderer *renderer, string texturePath, int maxAnimations, Vector2f*  initPos)
{
    //setup max animations
    this->maxAnimations = maxAnimations;

    // Allocate position and velocity - set values
    position = new Vector2f(initPos);
    velocity = new Vector2f();
    velocity->zero();

    // Create player texture from file, optimised for renderer
    texture = createTextureFromFile(texturePath.c_str(), renderer);

    if (texture == nullptr)
        throw std::runtime_error("File not found!");

    // create array of pointers to animations. 
    // child classes will have to init these!
    animations = new Animation*[maxAnimations];

    // Allocate memory for the animation structures
    for (int i = 0; i < maxAnimations; i++)
    {
        animations[i] = new Animation();
    }

}

/**
 * ~Sprite
 * 
 * Destroys the Sprite and any associated 
 * objects 
 * 
 */
Sprite::~Sprite()
{
    // Deallocate memory
    // set pointers back to null (stale pointer).
    delete position;
    position = nullptr;

    delete velocity;
    velocity = nullptr;

    // Clean up animations - free memory
    for (int i = 0; i < maxAnimations; i++)
    {
        // Clean up the animaton structure
        // allocated with new so use delete.
        delete animations[i];
        animations[i] = nullptr;
    }

    delete [] animations;
    animations = nullptr;

    delete aabb;
    aabb = nullptr;

    // Clean up
    SDL_DestroyTexture(texture);
    texture = nullptr;
}

/**
 * draw
 * 
 * Method draw a Player object
 * 
 * @param renderer SDL_Renderer to draw to
 */
void Sprite::draw(SDL_Renderer *renderer)
{

    // Get current animation based on the state.
    Animation *current = this->animations[getCurrentAnimationState()];

    if (angle == -1) {
        SDL_RenderCopy(renderer, texture, current->getCurrentFrame(), &targetRectangle);

    }
    else {
        SDL_RenderCopyEx(renderer,
            texture,
            current->getCurrentFrame(),
            &targetRectangle,
            angle,
            NULL,
            SDL_FLIP_NONE);
    }
}

/**
 * update
 * 
 * Method to update the Sprite 
 * 
 * @param timeDeltaInSeconds the time delta in seconds
 */
void Sprite::update(float timeDeltaInSeconds)
{
    // Calculate distance travelled since last update
    Vector2f movement(velocity);
    movement.scale(timeDeltaInSeconds);

    // Update player position.
    position->add(&movement);

    // Move sprite to nearest pixel location.
    targetRectangle.x = round(position->getX());
    targetRectangle.y = round(position->getY());

    // Get current animation
    Animation *current = animations[getCurrentAnimationState()];

    // let animation update itself.
    current->update(timeDeltaInSeconds);

    // Move bounding box
    if(aabb != nullptr)
        aabb->setPosition(position);
}

 Vector2f* Sprite::getPosition()
 {
     return position;
 }

void Sprite::setPosition(Vector2f* pos)
{
    this->position = new Vector2f(pos);
}

 AABB* Sprite::getAABB()
 {
     return aabb;
 }