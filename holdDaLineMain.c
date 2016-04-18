#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <time.h>
//DEBUG
#include <stdlib.h>

//-------------PROTOTYPE STRUCTS-----------------//
#define MAX_BULLETS 100
#define MAX_KRAUTS 100
#define MAX_TANKS 1

typedef struct
{
  float x;
  float y;
  float dx;
}Bullet;

typedef struct
{
   float x;
   float y;
   float dx;
   int inRange;
   int isFire; //Whenever Kraut enters a killzone will run a test to see if kraut will fire. Once run isFire will prevent it from running again
   int willFire; //Indicates if Kraut will fire
   int dead;
}Kraut;

typedef struct
{
   float x;
   float y;
   float dx;
   int life;
   int dead;
}Tank;

typedef struct
{
   float x;
   float y;
   float dx;
}testCube;

typedef struct
{
  float x;
  float y;
}Cursor;

typedef struct
{
  int x;
  int y;
  char *name;
  int selected;
  int gunFired;
}Solider;

typedef struct
{
  Solider leftGunner;
  Solider mainGunner;
  Solider rightGunner;
  int fireStart;

  //Font and Textures
  TTF_Font *font;
  SDL_Texture *titleBlocText;
  SDL_Texture *soliderRedText;

  //Animation Data for titleBloc and SoliderRed
  float titleY;
  float titleDX;

  float soliderRedY;
  float soliderRedDX;

  //Indicates that the title Screen animation is not yet done
  int introFin;

  //Gunfire timers
  clock_t lastFireLeft;
  clock_t nowFireLeft;

  clock_t lastFire;
  clock_t nowFire;

  clock_t lastFireRight;
  clock_t nowFireRight;

  //Kraut Spawn timers
  clock_t lastkrtSpawn;
  clock_t nowkrtSpawn;

  //DEBUG Tank Spawn timers
  clock_t lastTankSpawn;
  clock_t nowTankSpawn;

  //Blinking Start Prompt
  clock_t blinkStart;
  clock_t blinkNow;

}Gamestate;

//Init BULLETS AND KRAUTS
Bullet *bulletsLeft[MAX_BULLETS] = {NULL};
Bullet *bullets[MAX_BULLETS] = {NULL};
Bullet *bulletsRight[MAX_BULLETS] = {NULL};
Kraut *krauts[MAX_KRAUTS] = {NULL};
Tank *tanks[MAX_TANKS] = {NULL};
Bullet *germanBullets[MAX_BULLETS] = {NULL};

#include "functions.h"
#include "render.h"
#include "process.h"

//---------------------MAIN---------------------//
int main(int argc, char *argv[])
{
    //Set Window, Set Renderer
    SDL_Window *window;
    SDL_Renderer *renderer;

    //SDL Init
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    window = SDL_CreateWindow("Game Window",            //Window Title
                              SDL_WINDOWPOS_UNDEFINED,  // Initial x position
                              SDL_WINDOWPOS_UNDEFINED,  // Initial y position
                              320,                      // Width in pixels
                              240,                      // Height in pixels
                              0                         // Flags
                              //SDL_WINDOW_FULLSCREEN
                              );
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    testScreenSize();
    //DEBUG
    srand(time(NULL));

    //Cursor
    Cursor reticule;
    reticule.x = 160.0;
    reticule.y = 120.0;

    //DEBUG Collision Block
    testCube collider;
    collider.x = 280.0;
    collider.y = 40.0;

    Gamestate game;
    loadGamestate(&game, renderer);

    //-----TITLE SCREEN LOOP-----//
    int gameStart = 0;
    while(!gameStart)
    {
        gameStart = gameStartTrig(&game);
        gameStartRend(renderer, &game);
    };

    //-----MAIN GAME LOOP-----//
    int done = 0;
    while(!done)
    {
        done = processEvents(window, &reticule, &collider, &game);
        doRender(renderer, &reticule, &collider, &game);
    };

    //SDL_Delay(2000);

    //End Processes
    dumpGamestate(&game);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_Quit();
    SDL_Quit();

    return 0;
}

//--------------------TRASH CODE---------------------//
/*
     //RED SCREEN
    redScreen(renderer, window);
    //GAME SCREEN
    gameScreen(renderer, window);

    //LOADING SCREEN
    //loadingScreen(renderer, window);

    //titleScreen(renderer, window);
    //DEBUG LOADING SCREEN
    //loadingScreen(renderer, window, &game);
*/
