#ifndef PLAYER_H_
#define PLAYER_H_

#include "SDL2Common.h"
#include "Sprite.h"

// Forward declerations
// improve compile time. 
class Vector2f;
class Animation;
class Game;

class Player : public Sprite
{
private:
    
    // Animation state
    int state;
        
    // Sprite information
    static const int SPRITE_HEIGHT = 32;
    static const int SPRITE_WIDTH = 32;

    // Bullet spawn
    float cooldownTimer;
    static const float COOLDOWN_MAX;

    Game* game;

    // Score
    int points;
public:
    Player();
    ~Player();

    // Player Animation states
    enum PlayerState{LEFT=0, RIGHT, UP, DOWN, IDLE};
    
    void init(SDL_Renderer *renderer);
    void processInput(const Uint8 *keyStates);

    void setGame(Game* game);
    void fire();

    int getCurrentAnimationState();

    //Overloads
    void update(float timeDeltaInSeconds);
    // score
    void addScore(int points);
    int getScore();
};



#endif