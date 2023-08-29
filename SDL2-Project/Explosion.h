#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "SDL2Common.h"
#include "Sprite.h"

// Forward declerations
// improve compile time. 
class Vector2f;
class Animation;
class Game;


class Explosion : public Sprite
{
private:
    // Sprite information
    static const int SPRITE_HEIGHT = 48;
    static const int SPRITE_WIDTH = 48;

    // Need game
    Game* game;
    float countDeathTime = 0;

public:
    Explosion(SDL_Renderer* renderer, Vector2f pos);
    ~Explosion();

    // Player Animation states

    void init(SDL_Renderer* renderer);
    void update(float timeDeltaInSeconds);

    void setGame(Game* game);

    int getCurrentAnimationState()
    {
        return 0;
    }

};

#endif