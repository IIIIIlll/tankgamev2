#ifndef BULLET_H_
#define BULLET_H_

#include "SDL2Common.h"
#include "Sprite.h"

// Forward declerations
// improve compile time. 
class Vector2f;
class Animation;
class Game;
class AABB;

class Bullet : public Sprite
{
private:
    
    // Animation state
    int state;
        
    // Sprite information
    static const int SPRITE_HEIGHT = 32;
    static const int SPRITE_WIDTH = 32;

    // need game
    Game *game;

    int damage;
    float lifetime;
    
    // angle in radians
    float orientation;

    // don't know the direction of the sprite
    // in the image I have?
    float angleOffset;
    float calculateOrientation(Vector2f* direction);

public:
    Bullet();
    ~Bullet();

    // Player Animation states
    enum BulletState{TRAVEL};
    
    void init(SDL_Renderer *renderer, Vector2f* position, Vector2f* direction);
    void update(float timeDeltaInSeconds);
    void draw(SDL_Renderer *renderer);

    int getCurrentAnimationState();

    int getDamage();
    bool hasExpired();

};

#endif