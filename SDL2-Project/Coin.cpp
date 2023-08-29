#include "Coin.h"
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
Coin::Coin(SDL_Renderer* renderer, Vector2f pos) : Sprite()
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
void Coin::init(SDL_Renderer* renderer)
{
    //path string
    string path("assets/images/MonedaR.png");

    //postion
    Vector2f position(300.0f, 300.0f);

    // Call sprite constructor
    Sprite::init(renderer, path, 6, &position);

    // Setup the animation structure
    animations[0]->init(5, SPRITE_WIDTH, SPRITE_HEIGHT, 1, 5);
    for (int i = 0; i < maxAnimations; i++)
    {
        animations[i]->setMaxFrameTime(0.05f);
    }

    aabb = new AABB(this->getPosition(), SPRITE_HEIGHT - 10, SPRITE_WIDTH - 10);
}

// used this coin pickup worksheet to guide me when implementing a similar mechanic in my game https://subscription.packtpub.com/book/game-development/9781786466198/9/ch09lvl1sec82/using+the+pickup+class.
Coin::~Coin()
{

}

void Coin::update(float dt)
{
    Sprite::update(dt);

    countDeathTime += dt;
    if (countDeathTime > 20) {
        destroyFlag = true;
    }
}


void Coin::setGame(Game* game)
{
    this->game = game;
}





