#include "Game.h"
#include "TextureUtils.h"

#include "Player.h"
#include "Player2.h"
#include "NPC.h"
#include "Bullet.h"
#include "Vector2f.h"
#include "AABB.h"
#include "Explosion.h"
#include "Coin.h"
#include "MSound.h"

//for printf
#include <cstdio>

// for exceptions
#include <stdexcept>
#include <time.h>
#include "EnemyBullet.h"

Game::Game()
{
    gameWindow = nullptr;
    gameRenderer = nullptr;

    backgroundTexture = nullptr;
    player = nullptr;

    keyStates = nullptr;

    quit = false;
}

void Game::init()
{

    srand(time(nullptr));
    gameWindow = SDL_CreateWindow("Ammar sdl2 Tank game v1.0",   // Window title
        SDL_WINDOWPOS_UNDEFINED, // X position
        SDL_WINDOWPOS_UNDEFINED, // Y position
        WINDOW_WIDTH,            // width
        WINDOW_HEIGHT,           // height               
        SDL_WINDOW_SHOWN);       // Window flags  

    if (gameWindow != nullptr)
    {
        // if the window creation succeeded create our renderer
        gameRenderer = SDL_CreateRenderer(gameWindow, 0, 0);

        if (gameRenderer == nullptr)
        {
            throw std::runtime_error("Error - SDL could not create renderer\n");
        }
    }
    else
    {
        // could not create the window, so don't try and create the renderer. 
        throw std::runtime_error("Error - SDL could not create Window\n");
    }

    // Track Keystates array
    keyStates = SDL_GetKeyboardState(NULL);

    // Create background texture from file, optimised for renderer 
    backgroundTexture = createTextureFromFile("assets/images/desert.png", gameRenderer);

    if (backgroundTexture == nullptr)
        throw std::runtime_error("Background image not found\n");

    //setup player
    player = new Player();
    player->init(gameRenderer);
    player->setGame(this);

    player2 = new Player2();
    player2->init(gameRenderer);
    player2->setGame(this);

    /*npc = new NPC();
    npc->init(gameRenderer);
    npc->setGame(this);*/
    //npc->respawn(WINDOW_HEIGHT, WINDOW_WIDTH);

    SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 255);
    // Colour provided as red, green, blue and alpha (transparency) values (ie. RGBA)

}




Game::~Game()
{
    //Clean up!
    delete player;
    player = nullptr;

    delete player2;
    player2 = nullptr;


    for (NPC* npc : npcs) {
        delete npc;
    }

    npcs.clear();

    for (vector<Bullet*>::iterator it = bullets.begin(); it != bullets.end();)
    {
        delete* it;
        *it = nullptr;
        it = bullets.erase(it);
    }

    SDL_DestroyTexture(backgroundTexture);
    backgroundTexture = nullptr;

    SDL_DestroyRenderer(gameRenderer);
    gameRenderer = nullptr;

    SDL_DestroyWindow(gameWindow);
    gameWindow = nullptr;
}

void Game::draw()
{
    // 1. Clear the screen
    SDL_RenderClear(gameRenderer);

    // 2. Draw the scene
    SDL_RenderCopy(gameRenderer, backgroundTexture, NULL, NULL);

    player->draw(gameRenderer);
    player2->draw(gameRenderer);

    for (NPC* npc : npcs) {
        npc->draw(gameRenderer);
    }

    for (Coin* c : coins) {
        c->draw(gameRenderer);
    }

    for (Explosion* e : explosions) {
        e->draw(gameRenderer);
    }

    for (int i = 0; i < bullets.size(); i++) {
        bullets[i]->draw(gameRenderer);
    }

    for (int i = 0; i < enemyBullets.size(); i++) {
        enemyBullets[i]->draw(gameRenderer);
    }

    // 2.5 Draw HUD
    printf("Player Score: %d\n", player->getScore());

    // 3. Present the current frame to the screen




    SDL_RenderPresent(gameRenderer);


}

void Game::update(float timeDelta)
{
    player->update(timeDelta);
    player2->update(timeDelta);

    //  if(npc->isDead())
        //  npc->respawn(WINDOW_HEIGHT, WINDOW_WIDTH);

      // spawn enemies
    if (npcs.size() < 2) {
        NPC* npc = new NPC();
        npc->init(gameRenderer);
        npc->setGame(this);
        npc->setPosition(new Vector2f(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT));
        npcs.push_back(npc);
    }
    if (coins.size() < 5) {
        coins.push_back(new Coin(gameRenderer, new Vector2f(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT)));
    }

    for (NPC* npc : npcs) {
        npc->update(timeDelta);
        npc->fire();
    }

    for (Coin* c : coins) {
        c->update(timeDelta);
    }

    for (Explosion* e : explosions) {
        e->update(timeDelta);
    }

    for (vector<Bullet*>::iterator it = bullets.begin(); it != bullets.end();)
    {
        if ((*it)->hasExpired())
        {
            delete* it;
            *it = nullptr;
            it = bullets.erase(it);
        }
        else
        {
            ++it;
        }
    }
    if (player->getScore() < -15)
    {
        SDL_Quit();
    }

    for (vector<Bullet*>::iterator it = bullets.begin(); it != bullets.end(); ++it)
    {
        (*it)->update(timeDelta);
    }
    for (vector<EnemyBullet*>::iterator it = enemyBullets.begin(); it != enemyBullets.end(); ++it)
    {
        (*it)->update(timeDelta);
    }

    collisionDetection();

}

void Game::processInputs()
{
    SDL_Event event;

    // Handle input 
    if (SDL_PollEvent(&event))  // test for events
    {
        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;

            // Key pressed event
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                quit = true;
                break;
            }
            break;

            // Key released event
        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                //  Nothing to do here.
                break;
            }
            break;

        default:
            // not an error, there's lots we don't handle. 
            break;
        }
    }

    // Process Inputs - for player 
    player->processInput(keyStates);
    player2->processInput(keyStates);
}

Player* Game::getPlayer()
{
    return player;
}

Player2* Game::getPlayer2()
{
    return player2;
}

void Game::runGameLoop()
{
    // Timing variables
    unsigned int currentTimeIndex;
    unsigned int timeDelta;
    float timeDeltaInSeconds;
    unsigned int prevTimeIndex;

    // initialise preTimeIndex
    prevTimeIndex = SDL_GetTicks();

    // Game loop
    while (!quit) // while quit is not true
    {
        // Calculate time elapsed
        // Better approaches to this exist 
        //- https://gafferongames.com/post/fix_your_timestep/
        currentTimeIndex = SDL_GetTicks();
        timeDelta = currentTimeIndex - prevTimeIndex; //time in milliseconds
        timeDeltaInSeconds = timeDelta * 0.001f;

        // Store current time index into prevTimeIndex for next frame
        prevTimeIndex = currentTimeIndex;

        // Process inputs
        processInputs();

        // Update Game Objects
        update(timeDeltaInSeconds);

        //Draw stuff here.
        draw();

        SDL_Delay(1);
    }
}

void Game::createBullet(Vector2f* position, Vector2f* direction)
{
    Bullet* bullet = new Bullet();

    bullet->init(gameRenderer, position, direction);

    bullets.push_back(bullet);
}

void Game::createEnemyBullet(Vector2f* position, Vector2f* direction)
{
    EnemyBullet* bullet = new EnemyBullet();

    bullet->init(gameRenderer, position, direction);

    enemyBullets.push_back(bullet);
}

void Game::collisionDetection()
{
    for (Coin* c : coins) {
        if (player->getAABB()->intersects(c->getAABB())) {
            c->destroyFlag = true;
            player->addScore(9);
            msound.playSound(MSound::COIN);
            continue;
        }

        if (player2->getAABB()->intersects(c->getAABB())) {
            c->destroyFlag = true;
            player2->addScore(9);
            msound.playSound(MSound::COIN);
            continue;
        }
    }

    for (Bullet* bullet : bullets)
    {
        for (NPC* npc : npcs) {
            if (npc->getAABB()->intersects(bullet->getAABB()))
            {
                // increase player score
                player->addScore(npc->getPoints());
                player2->addScore(npc->getPoints());

                // damage npc
                npc->takeDamage(bullet->getDamage());

                bullet->destroyFlag = true;
                msound.playSound(MSound::EXPLOSION);
                explosions.push_back(new Explosion(gameRenderer, Vector2f(bullet->getPosition()->getX() - 12, bullet->getPosition()->getY() - 12)));
            }
        }
        for (EnemyBullet* enemyBullet : enemyBullets) {
            if (enemyBullet->getAABB()->intersects(bullet->getAABB()))
            {
                enemyBullet->destroyFlag = true;
                bullet->destroyFlag = true;
                msound.playSound(MSound::EXPLOSION);
                explosions.push_back(new Explosion(gameRenderer, Vector2f(bullet->getPosition()->getX() - 12, bullet->getPosition()->getY() - 12)));
            }
        }
    }

    for (EnemyBullet* enemyBullet : enemyBullets) {
        if (player->getAABB()->intersects(enemyBullet->getAABB()))
        {
            player->addScore(-5);
            enemyBullet->destroyFlag = true;
            msound.playSound(MSound::EXPLOSION);
            explosions.push_back(new Explosion(gameRenderer, Vector2f(enemyBullet->getPosition()->getX() - 12, enemyBullet->getPosition()->getY() - 12)));
        }

        if (player2->getAABB()->intersects(enemyBullet->getAABB()))
        {
            player2->addScore(-5);
            enemyBullet->destroyFlag = true;
            msound.playSound(MSound::EXPLOSION);
            explosions.push_back(new Explosion(gameRenderer, Vector2f(enemyBullet->getPosition()->getX() - 12, enemyBullet->getPosition()->getY() - 12)));
        }
    }


    // delete
    for (int i = 0; i < bullets.size(); i++)
    {
        if (bullets[i]->destroyFlag) {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
            ;
        }
    }
    for (int i = 0; i < enemyBullets.size(); i++)
    {
        if (enemyBullets[i]->destroyFlag) {
            delete enemyBullets[i];
            enemyBullets.erase(enemyBullets.begin() + i);
            ;
        }
    }

    for (int i = 0; i < npcs.size(); i++)
    {
        if (npcs[i]->destroyFlag) {
            delete npcs[i];
            npcs.erase(npcs.begin() + i);
        }
    }

    for (int i = 0; i < explosions.size(); i++)
    {
        if (explosions[i]->destroyFlag) {
            delete explosions[i];
            explosions.erase(explosions.begin() + i);
        }
    }

    for (int i = 0; i < coins.size(); i++)
    {
        if (coins[i]->destroyFlag) {
            delete coins[i];
            coins.erase(coins.begin() + i);
        }
    }


}
