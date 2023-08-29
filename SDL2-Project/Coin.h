#ifndef COIN_H_
#define COIN_H_

#include "SDL2Common.h"
#include "Sprite.h"

// Forward declerations
// improve compile time. 
class Vector2f;
class Animation;
class Game;


class Coin : public Sprite
{
private:
    // Sprite information
    static const int SPRITE_HEIGHT = 16;
    static const int SPRITE_WIDTH = 16;

    // Need game
    Game* game;
    float countDeathTime = 0;

public:
    Coin(SDL_Renderer* renderer, Vector2f pos);
    ~Coin();

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