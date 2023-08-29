#include "Explosion.h"
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
Explosion::Explosion(SDL_Renderer* renderer,Vector2f pos) : Sprite()
{

    targetRectangle.w = SPRITE_WIDTH;
    targetRectangle.h = SPRITE_HEIGHT;
    init(renderer);
    setPosition(new Vector2f(pos.getX(), pos.getY()));
}

/**
 * init
 *
 * Function to populate an animation structure from given paramters.
 *
 * @param renderer Target SDL_Renderer to use for optimisation.
 * @exception Throws an exception on file not found or out of memory.
 */
void Explosion::init(SDL_Renderer* renderer)
{
    //path string
    string path("assets/images/explo1.png");

    //postion
    Vector2f position(300.0f, 300.0f);

    // Call sprite constructor
    Sprite::init(renderer, path, 6, &position);

    // Setup the animation structure
    animations[0]->init(10, SPRITE_WIDTH, SPRITE_HEIGHT, 1, 10);
    for (int i = 0; i < maxAnimations; i++)
    {
        animations[i]->setMaxFrameTime(0.05f);
    }

    aabb = new AABB(this->getPosition(), SPRITE_HEIGHT - 10, SPRITE_WIDTH - 10);
}


Explosion::~Explosion()
{

}
// this make a update when the bullet hits the object and then destroys it 
void Explosion::update(float dt)
{
    Sprite::update(dt);

    countDeathTime += dt;
    if (countDeathTime > 0.5) {
        destroyFlag = true;
    }
}


void Explosion::setGame(Game* game)
{
    this->game = game;
}





