#include "Player2.h"
#include "Animation.h"
#include "Vector2f.h"
#include "TextureUtils.h"
#include "Game.h"
#include "AABB.h"

#include <stdexcept>
#include <string>

using std::string;

// Only types with a fixed bit representaition can be
// defined in the header file
const float Player2::COOLDOWN_MAX = 0.2f;

/**
 * Player
 *
 * Constructor, setup all the simple stuff. Set pointers to null etc.
 *
 */
Player2::Player2() : Sprite()
{
    state = IDLE;
    speed = 150.0f;

    targetRectangle.w = SPRITE_WIDTH;
    targetRectangle.h = SPRITE_HEIGHT;

    // Initialise weapon cooldown. 
    cooldownTimer = 0;

    // Init points
    points = 0;
}

/**
 * initPlayer
 *
 * Function to populate an animation structure from given paramters.
 *
 * @param renderer Target SDL_Renderer to use for optimisation.
 * @exception Throws an exception on file not found or out of memory.
 */
void Player2::init(SDL_Renderer* renderer)
{
    //path string
    string path("assets/images/tank_blue.png");

    //postion
    Vector2f position(400.0f, 200.0f);

    // Call sprite constructor
    Sprite::init(renderer, path, 5, &position);

    // Setup the animation structure
    animations[LEFT]->init(1, SPRITE_WIDTH, SPRITE_HEIGHT, 1, 1);
    animations[RIGHT]->init(1, SPRITE_WIDTH, SPRITE_HEIGHT, 1, 1);
    animations[UP]->init(1, SPRITE_WIDTH, SPRITE_HEIGHT, 1, 1);
    animations[DOWN]->init(1, SPRITE_WIDTH, SPRITE_HEIGHT, 1, 1);
    animations[IDLE]->init(1, SPRITE_WIDTH, SPRITE_HEIGHT, 1, 1);

    for (int i = 0; i < maxAnimations; i++)
    {
        animations[i]->setMaxFrameTime(0.2f);
    }

    aabb = new AABB(this->getPosition(), SPRITE_HEIGHT, SPRITE_WIDTH);

}

/**
 * ~Player
 *
 * Destroys the player and any associated
 * objects
 *
 */
Player2::~Player2()
{

}

/**
 * processInput
 *
 * Method to process inputs for the player
 * Note: Need to think about other forms of input!
 *
 * @param keyStates The keystates array.
 */
void Player2::processInput(const Uint8* keyStates)
{
    // Process Player Input

    //Input - keys/joysticks?
    float verticalInput = 0.0f;
    float horizontalInput = 0.0f;

    // If no keys are down player should not animate!
    state = IDLE;

    // This could be more complex, e.g. increasing the vertical
    // input while the key is held down.
    if (keyStates[SDL_SCANCODE_W])
    {
        verticalInput = -1.0f;
        state = UP;
        angle = 180;
    }

    if (keyStates[SDL_SCANCODE_S])
    {
        verticalInput = 1.0f;
        state = DOWN;
        angle = 0;
    }

    if (keyStates[SDL_SCANCODE_D])
    {
        horizontalInput = 1.0f;
        state = RIGHT;
        angle = -90;
    }

    if (keyStates[SDL_SCANCODE_A])
    {
        horizontalInput = -1.0f;
        state = LEFT;
        angle = 90;
    }

    // Calculate player velocity.
    velocity->setX(horizontalInput);
    velocity->setY(verticalInput);
    velocity->normalise();
    velocity->scale(speed);

    if (keyStates[SDL_SCANCODE_Q])
    {
        fire();
    }
}

int Player2::getCurrentAnimationState()
{
    return state;
}

void Player2::setGame(Game* game)
{
    this->game = game;
}

void Player2::update(float timeDeltaInSeconds)
{
    Sprite::update(timeDeltaInSeconds);

    cooldownTimer += timeDeltaInSeconds;


    // window check
    if (position->getX() < 0) {
        position->setX(0);
    }
    if (position->getY() < 0) {
        position->setY(0);
    }
    if (position->getX() > game->WINDOW_WIDTH - 32) {
        position->setX(game->WINDOW_WIDTH - 32);
    }
    if (position->getY() > game->WINDOW_HEIGHT - 32) {
        position->setY(game->WINDOW_HEIGHT - 32);
    }

}

void Player2::fire()
{
    // Need a cooldown timer, otherwise we shoot 
    // a million bullets a second and our npc
    // dies instantly
    if (cooldownTimer > COOLDOWN_MAX)
    {
        // Can't fire in idle state!
        float x = cos((90 + angle) * (3.14 / 180));
        float y = sin((90 + angle) * (3.14 / 180));
        Vector2f dir = Vector2f(x, y);
        game->createBullet(position, &dir);
        cooldownTimer = 0;
    }
}

void Player2::addScore(int points)
{
    this->points += points;
}

int Player2::getScore()
{
    return points;
}