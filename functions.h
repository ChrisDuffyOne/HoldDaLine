/*---------------------------------------
    FUNCTION DECLARATIONS
----------------------------------------*/

/*Retrieves the screen size in pixels that the window is currently being displayed in*/
void testScreenSize();

/*Title Screen that test text output*/
void titleScreen(SDL_Renderer *renderer, SDL_Window *window);

/*Red Screen picturing Soviet Soilders, used to test png render*/
void redScreen(SDL_Renderer *renderer, SDL_Window *window);

/*Game Screen loads the destoryed cityscape where the main game will take place*/
void gameScreen(SDL_Renderer *renderer, SDL_Window *window);

/*Capture key presses for loop*/
int processEvents(SDL_Window *window, Cursor *reticule, testCube *collider, Gamestate *game);

/*Useful utility function to see if two rectangles are colliding at all*/
int collide2d(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2);

/*Loading Screen*/
void loadingScreen(SDL_Renderer *renderer, SDL_Window *window);

/*Spawn Kraut*/
void spawnKraut(float x, float y);

/*Kill Kraut*/
void killKraut(int i);

/*Add a Bullet to the Gamescreen*/
void addBullet(float x, float y, Bullet *bulletArray[]);

/*Remove Bullet*/
void removeBullet(int i, Bullet *bulletArray[]);

/*Load Game*/
void loadGamestate(Gamestate *game);

/*Render sprites and move them about the game field*/
//void doRender(SDL_Renderer *renderer, Cursor *reticule, testCube *testBox, Gamestate *game);

/*---------------------------------------
    DEFINITION LINK
----------------------------------------*/
#include "functions.c"
