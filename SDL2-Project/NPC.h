#ifndef NPC_H_
#define NPC_H_

#include "SDL2Common.h"
#include "Sprite.h"

// Forward declerations
// improve compile time. 
class Vector2f;
class Animation;
class Game;


class NPC : public Sprite
{
private:

    // Animation state
    int state;

    // Sprite information
    static const int SPRITE_HEIGHT = 32;
    static const int SPRITE_WIDTH = 32;

    // Need game
    Game* game;

    // weapon range
    float maxRange;
    float timeToTarget;

    // npc health
    int health;

    // point value
    // set this at creation?
    int points;
    float coolDownTime = 0;

public:
    NPC();
    ~NPC();

    // Player Animation states
    enum NPCState { LEFT = 0, RIGHT, UP, DOWN, IDLE, DEAD };

    void init(SDL_Renderer* renderer);
    void update(float timeDeltaInSeconds);

    // Update 'things' ai related

    void ai();
    void setGame(Game* game);
    void fire();

    int getCurrentAnimationState();

    // damage / death / respawn
    void takeDamage(int damage);
    bool isDead();
    void respawn(const int MAX_HEIGHT, const int MAX_WIDTH);
    // score 
    int getPoints();
    void setPoints(int pointValue);

};

#endif