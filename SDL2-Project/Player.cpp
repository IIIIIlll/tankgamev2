#include "Player.h"
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
const float Player::COOLDOWN_MAX = 0.2f;

/**
 * Player
 * 
 * Constructor, setup all the simple stuff. Set pointers to null etc. 
 *  
 */
Player::Player() : Sprite()
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
void Player::init(SDL_Renderer *renderer)
{
    //path string
    string path("assets/images/tank_green.png");

    //postion
    Vector2f position(200.0f,200.0f);

    // Call sprite constructor
    Sprite::init(renderer, path, 5, &position);

    // Setup the animation structure
    animations[LEFT]->init(1, SPRITE_WIDTH, SPRITE_HEIGHT, 1,1);
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
Player::~Player()
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
void Player::processInput(const Uint8 *keyStates)
{
    // Process Player Input

    //Input - keys/joysticks?
    float verticalInput = 0.0f;
    float horizontalInput = 0.0f;

    // If no keys are down player should not animate!
    state = IDLE;

    // This could be more complex, e.g. increasing the vertical
    // this is the pacman style of rotation i added into my players movement it with its 4 states.here is a link of packman as refrence 
    // https://www.youtube.com/watch?v=lDkUoojxaAU https://stackoverflow.com/questions/2259476/rotating-a-point-about-another-point-2d here i followed to guide me on my rotation for my player movement.
    if (keyStates[SDL_SCANCODE_UP])
    {
        verticalInput = -1.0f;
        state = UP;
        angle = 180;
    }

    if (keyStates[SDL_SCANCODE_DOWN])
    {
        verticalInput = 1.0f;
        state = DOWN;
        angle = 0;
    }

    if (keyStates[SDL_SCANCODE_RIGHT])
    {
        horizontalInput = 1.0f;
        state = RIGHT;
        angle = -90;
    }

    if (keyStates[SDL_SCANCODE_LEFT])
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

    if (keyStates[SDL_SCANCODE_SPACE])
    {
        fire();
    }
}
// this gets the players current animation state
int Player::getCurrentAnimationState()
{
    return state;
}
// this sets the animation
void Player::setGame(Game* game)
{
    this->game = game;
}

void Player::update(float timeDeltaInSeconds)
{
    Sprite::update(timeDeltaInSeconds);

    cooldownTimer += timeDeltaInSeconds;


    // window check this is to create the overal bounding box collision so player and npc dont leave the screen
    if (position->getX() < 0) {
        position->setX(0);
    }
    if (position->getY() < 0) {
        position->setY(0);
    }
    if (position->getX() > game->WINDOW_WIDTH-32) {
        position->setX(game->WINDOW_WIDTH - 32);
    }
    if (position->getY() > game->WINDOW_HEIGHT - 32) {
        position->setY(game->WINDOW_HEIGHT - 32);
    }

}

void Player::fire()
{   
    // Need a cooldown timer, otherwise we shoot 
    // a million bullets a second and our npc
    // dies instantly
    if(cooldownTimer > COOLDOWN_MAX)
    {
        // Can't fire in idle state!
        float x = cos((  90 + angle) * (3.14 / 180)) ;
        float y = sin((  90 + angle) * (3.14 / 180)) ;
        Vector2f dir = Vector2f(x, y);
        game->createBullet(position, &dir);
        cooldownTimer = 0;
    }   
}
// this is to see if when it is voided it adds the players score
void Player::addScore(int points)
{
    this->points += points;
}
// this checks score and inputs a remainder points 
int Player::getScore()
{
    return points;
}