/*-----------------------------------------------------
        TESTSCREENSIZE
-----------------------------------------------------*/
void testScreenSize()
{
    SDL_DisplayMode current;
    for(int i = 0; i < SDL_GetNumVideoDisplays(); ++i)
    {
        int should_be_zero = SDL_GetCurrentDisplayMode(i, &current);
        if(should_be_zero != 0)
        {
            SDL_Log("Could not get display mode for video display #%d: %s", i, SDL_GetError());
        }
        else
        {
            SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz. \n", i, current.w, current.h, current.refresh_rate);
        }
    };
};

/*-----------------------------------------------------
        TITLESCREEN
-----------------------------------------------------*/
void titleScreen(SDL_Renderer *renderer, SDL_Window *window)
{
  //Make type
  TTF_Font *font;
  char *fontPath = SDL_GetBasePath();
  strcat(fontPath, "fonts/Crazy-Pixel.ttf");
  font = TTF_OpenFont(fontPath, 48);

  SDL_Color red = {255, 0, 0, 255};
  SDL_Surface *temp = TTF_RenderText_Blended(font,"Hold Da Line",red);

  SDL_Texture *label;
  label = SDL_CreateTextureFromSurface(renderer, temp);
  SDL_FreeSurface(temp);

  //Set Background to White
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);

  //Set Text to Screen
  SDL_Rect textRect = {30, 80, 150, 80};
  SDL_RenderCopy(renderer, label, NULL, &textRect);

  SDL_RenderPresent(renderer);
  SDL_Delay(2000);

  //End Processes
  SDL_DestroyTexture(label);
}

/*-----------------------------------------------------
        REDSCREEN
-----------------------------------------------------*/
void redScreen(SDL_Renderer *renderer, SDL_Window *window){

  //PATH Solider
  char *imgPath = SDL_GetBasePath();
  strcat(imgPath, "pngs/soilders.png");

  //SURFACE LOAD
  SDL_Surface *soliderRed = NULL;
  soliderRed = IMG_Load(imgPath);

  //SURFACE TO TEXTURE LOAD
  SDL_Texture *soliderRedText;
  soliderRedText = SDL_CreateTextureFromSurface(renderer, soliderRed);

  //FREE SURFACE
  SDL_FreeSurface(soliderRed);

  //CREATE RECT AND ADD TEXTURE TO IT
  SDL_Rect soliderRedRect = { 0, 0, 320, 240};
  SDL_RenderCopy(renderer, soliderRedText, NULL, &soliderRedRect);

  //PRESENT
  SDL_RenderPresent(renderer);

  SDL_Delay(2000);
}

/*-----------------------------------------------------
        GAMESCREEN
-----------------------------------------------------*/
void gameScreen(SDL_Renderer *renderer, SDL_Window *window){
  //PATH game
  char *imgPath = SDL_GetBasePath();
  strcat(imgPath, "pngs/gameScreen_320.png");

  //SURFACE LOAD
  SDL_Surface *gameScreenSurface = NULL;
  gameScreenSurface = IMG_Load(imgPath);

  //SURFACE TO TEXTURE LOAD
  SDL_Texture *gameScreenText;
  gameScreenText = SDL_CreateTextureFromSurface(renderer, gameScreenSurface);

  //FREE SURFACE
  SDL_FreeSurface(gameScreenSurface);

  //CREATE RECT AND ADD TEXTURE TO IT
  SDL_Rect gameScreenRect = { 0, 0, 320, 240};
  SDL_RenderCopy(renderer, gameScreenText, NULL, &gameScreenRect);

  //PRESENT
  SDL_RenderPresent(renderer);

  SDL_Delay(10000);
};

/*-----------------------------------------------------
        COLLIDE2D
-----------------------------------------------------*/
int collide2d(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2)
{
  return (!((x1 > (x2+wt2)) || (x2 > (x1+wt1)) || (y1 > (y2+ht2)) || (y2 > (y1+ht1))));
};

/*-----------------------------------------------------
        LOADINGSCREEN
-----------------------------------------------------*/
void loadingScreen(SDL_Renderer *renderer, SDL_Window *window){

  //Make type
  TTF_Font *font;
  char *fontPath = SDL_GetBasePath();
  strcat(fontPath, "fonts/Crazy-Pixel.ttf");
  font = TTF_OpenFont(fontPath, 48);

  SDL_Color white = {255, 255, 255, 255};
  SDL_Surface *temp = TTF_RenderText_Blended(font,"LOADING",white);

  SDL_Texture *label;
  label = SDL_CreateTextureFromSurface(renderer, temp);
  SDL_FreeSurface(temp);

  //Set Background to Red
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderClear(renderer);

  //Set Text to Screen
  SDL_Rect textRect = {30, 80, 150, 80};
  SDL_RenderCopy(renderer, label, NULL, &textRect);

  SDL_RenderPresent(renderer);
  SDL_Delay(2000);

  //End Processes
  SDL_DestroyTexture(label);
}

/*-----------------------------------------------------
        SPAWNKRAUT
-----------------------------------------------------*/
void spawnKraut(float x, float y)
{
    int found = -1;
    for(int i = 0; i < MAX_KRAUTS; i++)
    {
        if(krauts[i] == NULL)
        {
            found = i;
            break;
        }
    }

    if(found >= 0)
    {
        krauts[found] = malloc(sizeof(Kraut));
        krauts[found]->x = x;
        krauts[found]->y = y;
        krauts[found]->dx = 1.0;
        krauts[found]->dead = 0;
    }
};

/*-----------------------------------------------------
        KILLKRAUT
-----------------------------------------------------*/
void killKraut(int i)
{
    if(krauts[i])
    {
        free(krauts[i]);
        krauts[i] = NULL;
    }
}
/*-----------------------------------------------------
        ADDBULLET
-----------------------------------------------------*/
void addBullet(float x, float y, Bullet *bulletArray[])
{
    int found = -1;
    for(int i = 0; i <MAX_BULLETS; i++)
    {
        if(bulletArray[i] == NULL)
        {
            found = i;
            break;
        }
    }

    if(found >= 0)
    {
        bulletArray[found] = malloc(sizeof(Bullet));
        bulletArray[found]->x = x;
        bulletArray[found]->y = y;
        bulletArray[found]->dx = 3.0;
    }
};

/*-----------------------------------------------------
        REMOVEBULLET
-----------------------------------------------------*/
void removeBullet(int k, Bullet *bulletArray[])
{
    if(bulletArray[k])
    {
        free(bulletArray[k]);
        bulletArray[k] = NULL;
    }
};


/*-----------------------------------------------------
        LOADGAMESTATE
-----------------------------------------------------*/
void loadGamestate(Gamestate *game)
{
    //Setup Gunner positions
    game->leftGunner.x = 5;
    game->leftGunner.y = 230;
    game->leftGunner.name = "leftGun";
    game->leftGunner.selected = 0;

    game->mainGunner.x = 160;
    game->mainGunner.y = 230;
    game->mainGunner.name = "mainGun";
    game->mainGunner.selected = 1;

    game->rightGunner.x = 315;
    game->rightGunner.y = 230;
    game->rightGunner.name = "rightGun";
    game->rightGunner.selected = 0;

    game->lastFireLeft = clock();
    game->lastFire = clock();
    game->lastFireRight = clock();
    game->lastkrtSpawn = clock();
};
