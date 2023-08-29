#ifndef SPRITE_H_
#define SPRITE_H_

#include "SDL2Common.h"

#include <string>
using std::string;

// Forward declarations
// improve compile time. 
class Vector2f;
class Animation;
class AABB;

class Sprite 
{
protected:
    
    // Texture which stores the sprite sheet (this
    // will be optimised).
    SDL_Texture*     texture;

    // Player properties
    SDL_Rect targetRectangle;
    float speed;
    Vector2f* position;
    Vector2f* velocity;
    // Animations
    int maxAnimations;
    Animation** animations;

    // bounding box
    AABB *aabb;
    float angle = -1;

public:
    bool destroyFlag = false;

    Sprite();
    virtual ~Sprite();

    virtual void init(SDL_Renderer *renderer, string texturePath, int maxAnimations, Vector2f* position);

    virtual void draw(SDL_Renderer *renderer);
    
    virtual void update(float timeDeltaInSeconds);

    virtual int getCurrentAnimationState() = 0;

    Vector2f* getPosition();
    void setPosition(Vector2f* pos);

    // Bounding box
    AABB* getAABB();

};

#endif