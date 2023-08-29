#ifndef GAME_H_
#define GAME_H_

#include "SDL2Common.h"
#include "MSound.h"
#include "EnemyBullet.h"


#include <vector>
using std::vector;

class Player;
class Player2;
class NPC;
class Bullet;
class Vector2f;
class Explosion;
class Coin;
class MSound;

class Game
{
private:
    // Declare window and renderer objects
    SDL_Window* gameWindow;
    SDL_Renderer* gameRenderer;

    // Background texture
    SDL_Texture* backgroundTexture;

    //Declare Player
    Player* player;
    Player2* player2;

    //Declare NPC
    vector<NPC*> npcs;

    // Bullets
    vector<Bullet*> bullets;
    vector<EnemyBullet*> enemyBullets;

    vector<Explosion*> explosions;
    vector<Coin*> coins;

    MSound msound;

    // Window control 
    bool            quit;

    // Keyboard
    const Uint8* keyStates;





    // Game loop methods. 
    void processInputs();
    void update(float timeDelta);
    void draw();

public:
    // Constructor 
    Game();
    ~Game();

    // Methods
    void init();
    void runGameLoop();
    Player* getPlayer();
    Player2* getPlayer2();
    void createBullet(Vector2f* position, Vector2f* direction);
    void createEnemyBullet(Vector2f* position, Vector2f* direction);
    void collisionDetection();
    void gameOver();



    // Public attributes
    static const int WINDOW_WIDTH = 800;
    static const int WINDOW_HEIGHT = 600;
};

#endif