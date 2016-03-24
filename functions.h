/*---------------------------------------
    FUNCTION DECLARATIONS
----------------------------------------*/

/*Retrieves the screen size in pixels that the window is currently being displayed in*/
void testScreenSize();

/*Title Screen with soliders*/
void titleScreen(SDL_Renderer *renderer, SDL_Window *window);

/*Wait for Game Start Loop*/
int gameStartTrig();

/*Game Start Render*/
void gameStartRend(SDL_Renderer *renderer, Gamestate *game);

/*Red Screen picturing Soviet Soilders, used to test png render*/
void redScreen(SDL_Renderer *renderer, SDL_Window *window);

/*Game Screen loads the destoryed cityscape where the main game will take place*/
void gameScreen(SDL_Renderer *renderer, SDL_Window *window);

/*Useful utility function to see if two rectangles are colliding at all*/
int collide2d(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2);

/*Loading Screen*/
void loadingScreen(SDL_Renderer *renderer, SDL_Window *window, Gamestate *game);

/*Spawn Kraut*/
void spawnKraut(float x, float y);

/*Kill Kraut*/
void killKraut(int i);

/*Add a Bullet to the Gamescreen*/
void addBullet(float x, float y, Bullet *bulletArray[]);

/*Remove Bullet*/
void removeBullet(int i, Bullet *bulletArray[]);

/*Load Game: Loads all fonts, pngs, and clocks needed for the functioning of the game*/
void loadGamestate(Gamestate *game, SDL_Renderer *renderer);

/*Dump Game: Destorys all textures and other malloc'ed resources that were used by Gamestate*/
void dumpGamestate(Gamestate *game);

/*---------------------------------------
    DEFINITION LINK
----------------------------------------*/
#include "functions.c"
