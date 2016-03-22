/*-----------------------------------------------------
        DORENDER
-----------------------------------------------------*/
void doRender(SDL_Renderer *renderer, Cursor *reticule, testCube *testBox, Gamestate *game)
{
    //clear background to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    //reticule render
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    SDL_Rect rect = {reticule->x, reticule->y, 2, 2};
    SDL_RenderFillRect(renderer, &rect);

    //left solider render
    SDL_Rect leftGunner = { game->leftGunner.x, game->leftGunner.y, 8, 8};
    if(game->leftGunner.selected == 1)
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); //set the drawing color to red
    else
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);  //set the drawing color to blue
    SDL_RenderFillRect(renderer, &leftGunner);

    //main solider render
    SDL_Rect mainGunner = { game->mainGunner.x, game->mainGunner.y, 8, 8};
    if(game->mainGunner.selected == 1)
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); //set the drawing color to red
    else
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);  //set the drawing color to blue
    SDL_RenderFillRect(renderer, &mainGunner);

    //right solider render
    SDL_Rect rightGunner = { game->rightGunner.x, game->rightGunner.y, 8, 8};
    if(game->rightGunner.selected == 1)
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); //set the drawing color to red
    else
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);  //set the drawing color to blue
    SDL_RenderFillRect(renderer, &rightGunner);

    //left bullet render
    for(int i=0; i<MAX_BULLETS;i++) if(bulletsLeft[i])
    {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_Rect bulletTry = { bulletsLeft[i]->x, bulletsLeft[i]->y, 2, 2};
        SDL_RenderFillRect(renderer, &bulletTry);
    };
    //main bullet render
    for(int i=0; i<MAX_BULLETS;i++) if(bullets[i])
    {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_Rect bulletTry = { bullets[i]->x, bullets[i]->y, 2, 2};
        SDL_RenderFillRect(renderer, &bulletTry);
    };
    //right bullet render
    for(int i=0; i<MAX_BULLETS;i++) if(bulletsRight[i])
    {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_Rect bulletTry = { bulletsRight[i]->x, bulletsRight[i]->y, 2, 2};
        SDL_RenderFillRect(renderer, &bulletTry);
    };

    //main kraut render
    for(int i=0; i< MAX_KRAUTS; i++) if(krauts[i])
    {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_Rect krautRun = { krauts[i]->x, krauts[i]->y, 20, 20};
        SDL_RenderFillRect(renderer, &krautRun);
    };

    //We are done drawing, "present" or show to the screen what we've drawn
    SDL_RenderPresent(renderer);
};
