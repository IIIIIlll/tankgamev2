#include "NPC.h"
#include "Animation.h"
#include "Vector2f.h"
#include "TextureUtils.h"
#include "Game.h"
#include "Player.h"
#include "AABB.h"

#include <stdexcept>
#include <string>

using std::string;

/**
 * NPC
 *
 * Constructor, setup all the simple stuff. Set pointers to null etc.
 *
 */
NPC::NPC() : Sprite()
{
    state = IDLE;
    speed = 30.0f;

    maxRange = 0.4f;
    timeToTarget = 0.25f;

    targetRectangle.w = SPRITE_WIDTH;
    targetRectangle.h = SPRITE_HEIGHT;

    // Could pass these in to change the difficulty
    // of a NPC for each level etc. 
    maxRange = 0.4f;
    timeToTarget = 0.25f;
    health = 100;
    points = 10;
}

/**
 * init
 *
 * Function to populate an animation structure from given paramters.
 *
 * @param renderer Target SDL_Renderer to use for optimisation.
 * @exception Throws an exception on file not found or out of memory.
 */
void NPC::init(SDL_Renderer* renderer)
{
    //path string
    string path("assets/images/tank_red.png");

    //postion
    Vector2f position(300.0f, 300.0f);

    // Call sprite constructor
    Sprite::init(renderer, path, 6, &position);

    // Setup the animation structure
    animations[LEFT]->init(1, SPRITE_WIDTH, SPRITE_HEIGHT, 1, 1);
    animations[RIGHT]->init(1, SPRITE_WIDTH, SPRITE_HEIGHT, 1, 1);
    animations[UP]->init(1, SPRITE_WIDTH, SPRITE_HEIGHT, 1, 1);
    animations[DOWN]->init(1, SPRITE_WIDTH, SPRITE_HEIGHT, 1, 1);
    animations[IDLE]->init(1, SPRITE_WIDTH, SPRITE_HEIGHT, 1, 1);
    animations[DEAD]->init(1, SPRITE_WIDTH, SPRITE_HEIGHT, 1, 1);

    animations[DEAD]->setLoop(false);

    for (int i = 0; i < maxAnimations; i++)
    {
        animations[i]->setMaxFrameTime(0.4f);
    }

    aabb = new AABB(this->getPosition(), SPRITE_HEIGHT - 10, SPRITE_WIDTH - 10);
}

/**
 * ~NPC
 *
 * Destroys the NPC and any associated
 * objects
 *
 */
NPC::~NPC()
{

}
// update
void NPC::update(float dt)
{

    coolDownTime += dt;

    if (state != DEAD) //don't move dead sprite
        ai();
    else
    {
        velocity->setX(0.0f);
        velocity->setY(0.0f);
    }

    angle = -90 + atan2(velocity->getY(), velocity->getX()) * 180 / 3.14;
    Sprite::update(dt);
}

/**
 * ai
 *
 * Adjusts the velocity / state of the NPC
 * to follow the player
 *
 */
void NPC::ai()
{
    // get player
    Player* player = game->getPlayer();

    // get distance to player
        // copy the player position
    Vector2f vectorToPlayer(player->getPosition());
    // subtract our position to get a vector to the player
    vectorToPlayer.sub(position);
    float distance = vectorToPlayer.length();

    // if player 'in range' stop and fire
    if (distance < maxRange)
    {
        // put fire code in here later!
    }
    else
    {
        // else - head for player

        // Could do with an assign in vector
        velocity->setX(vectorToPlayer.getX());
        velocity->setY(vectorToPlayer.getY());

        // will work but 'wobbles'
        //velocity->scale(speed);   

        // Arrive pattern 
        velocity->scale(timeToTarget);

        if (velocity->length() > speed)
        {
            velocity->normalise();
            velocity->scale(speed);
        }

        state = IDLE;

        if (velocity->getY() > 0.1f)
            state = DOWN;
        else
            if (velocity->getY() < -0.1f)
                state = UP;
        // empty else is not an error!

        if (velocity->getX() > 0.1f)
            state = RIGHT;
        else
            if (velocity->getX() < -0.1f)
                state = LEFT;
        // empty else is not an error. 
    }
}

void NPC::setGame(Game* game)
{
    this->game = game;
}

int NPC::getCurrentAnimationState()
{
    return state;
}

void NPC::takeDamage(int damage)
{
    health -= damage;

    if (!(health > 0)) {
        state = DEAD;
        destroyFlag = true;
    }
}
// this is for npc fire this code is just the angle that the bullet fires and also creating the bullet.
void NPC::fire()
{
    if (coolDownTime >= 2.0f) {
        coolDownTime = 0;
        float x = cos((90 + angle) * (3.14 / 180));
        float y = sin((90 + angle) * (3.14 / 180));
        Vector2f dir = Vector2f(x, y);
        game->createEnemyBullet(position, &dir);
    }

}

bool NPC::isDead()
{
    if (health > 0)
        return false;
    else
        return true;
}
// respawn then to idle state
void NPC::respawn(const int MAX_HEIGHT, const int MAX_WIDTH)
{
    health = 150;
    state = IDLE;

    Vector2f randomPostion;

    int doubleWidth = MAX_WIDTH * 2;
    int doubleHeight = MAX_HEIGHT * 2;

    // get a random number between 0 and 
    // 2 x screen size. 
    int xCoord = rand() % doubleWidth;
    int yCoord = rand() % doubleHeight;

    // if its on screen move it off. 
    if (xCoord < MAX_WIDTH)
        xCoord *= -1;

    if (yCoord < MAX_HEIGHT)
        yCoord *= -1;

    randomPostion.setX(xCoord);
    randomPostion.setY(yCoord);

    this->setPosition(&randomPostion);
}
// this code here is when the player eliminates the npc the get points gives the value of the score to the player.
int NPC::getPoints()
{
    return points;
}

void NPC::setPoints(int pointValue)
{
    points = 120;
}
