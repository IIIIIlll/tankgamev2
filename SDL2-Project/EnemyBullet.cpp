#include "EnemyBullet.h"
#include "Animation.h"
#include "Vector2f.h"
#include "TextureUtils.h"
#include "Game.h"
#include "AABB.h"

#include <stdexcept>
#include <string>
#include <cmath> //for acos
#include <iostream>

using std::string;

/**
 * Bullet
 *
 * Constructor, setup all the simple stuff. Set pointers to null etc.
 *
 */
EnemyBullet::EnemyBullet() : Sprite()
{
    state = TRAVEL;
    speed = 200.0f;

    orientation = 0.0f;
    damage = 10;
    lifetime = 5.0f;
    targetRectangle.w = SPRITE_WIDTH;
    targetRectangle.h = SPRITE_HEIGHT;

    //Need to change this based on the image
    //being used.
    angleOffset = -90.0f;

}

/**
 * init
 *
 * Function to populate an animation structure from given paramters.
 *
 * @param renderer Target SDL_Renderer to use for optimisation.
 * @exception Throws an exception on file not found or out of memory.
 */
void EnemyBullet::init(SDL_Renderer* renderer, Vector2f* position, Vector2f* direction)
{
    // set orientation
    //this->orientation = calculateOrientation(direction);

    //std::cout << orientation << std::endl;

    //path string
    string path("assets/images/bullets.png");

    // Call sprite constructor
    Sprite::init(renderer, path, 1, position);

    // set velocity to forward direction of travel
    velocity->setX(direction->getX());
    velocity->setY(direction->getY());
    velocity->normalise();
    velocity->scale(speed);

    // Setup the animation structure
    animations[TRAVEL]->init(4, SPRITE_WIDTH, SPRITE_HEIGHT, 1, 4);

    for (int i = 0; i < maxAnimations; i++)
    {
        animations[i]->setMaxFrameTime(0.05f);
    }

    aabb = new AABB(new Vector2f(this->getPosition()->getX() - 8, this->getPosition()->getY() - 8), SPRITE_HEIGHT / 2, SPRITE_WIDTH / 2);
}

float EnemyBullet::calculateOrientation(Vector2f* direction)
{
    float angle = atan2f(direction->getY(), direction->getX()); //get angle (0,2pi)
    angle *= (180.0f / 3.142f); //convert to degrees
    return angle + angleOffset;
}

/**
 * ~Bullet
 *
 * Destroys the Bullet and any associated
 * objects
 *
 */
EnemyBullet::~EnemyBullet()
{

}

void EnemyBullet::update(float dt)
{
    angle = 0 + atan2(velocity->getY(), velocity->getX()) * 180 / 3.14;

    lifetime -= dt;
    Sprite::update(dt);

}

void EnemyBullet::draw(SDL_Renderer* renderer)
{
    // Get current animation based on the state.
    Sprite::draw(renderer);
}

int EnemyBullet::getCurrentAnimationState()
{
    return state;
}

int EnemyBullet::getDamage()
{
    return damage;
}

bool EnemyBullet::hasExpired()
{
    if (lifetime > 0.0f)
        return false;
    else
        return true;
}
