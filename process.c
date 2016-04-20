/*-----------------------------------------------------
        PROCESSEVENTS
-----------------------------------------------------*/
int processEvents(SDL_Window *window, Cursor *reticule, testCube *collider, Gamestate *game)
{
  SDL_Event event;
  int done = 0;

  //---------------------------- Endgame Event ----------------------------//
  while(SDL_PollEvent(&event))
  {
    switch(event.type)
    {
      case SDL_WINDOWEVENT_CLOSE:
      {
        if(window)
        {
          SDL_DestroyWindow(window);
          window = NULL;
          done = 1;
        }
      }
      break;
      case SDL_KEYDOWN:
      {
        switch(event.key.keysym.sym)
        {
          case SDLK_ESCAPE:
            done = 1;
          break;
        }
      }
      break;
      case SDL_QUIT:
        done = 1;
      break;
    }
  }

  //---------------------------- Control Event ----------------------------//
  const Uint8 *state = SDL_GetKeyboardState(NULL);
  if(state[SDL_SCANCODE_LEFT])
  {
    reticule->x -= 1.0;
    //printf("Cursor x: %f \n", reticule->x);
    game->leftGunner.selected = 1;
    game->mainGunner.selected = 0;
    game->rightGunner.selected = 0;
  }
  if(state[SDL_SCANCODE_RIGHT])
  {
    reticule->x += 1.0;
    //printf("Cursor x: %f \n", reticule->x);
    game->leftGunner.selected = 0;
    game->mainGunner.selected = 0;
    game->rightGunner.selected = 1;
  }
  if(state[SDL_SCANCODE_UP])
  {
    reticule->y -= 1.0;
    //printf("Cursor y: %f \n", reticule->y);
  }
  if(state[SDL_SCANCODE_DOWN])
  {
     reticule->y += 1.0;
     //printf("Cursor y: %f \n", reticule->y);
  }
  if(!state[SDL_SCANCODE_LEFT] && !state[SDL_SCANCODE_RIGHT])
  {
    game->leftGunner.selected = 0;
    game->mainGunner.selected = 1;
    game->rightGunner.selected = 0;
  }

  // Fire Left Gunner
  //if(game->leftGunner.selected == 1 && state[SDL_SCANCODE_SPACE])
  if(game->leftGunner.selected == 1 && state[SDL_SCANCODE_SPACE] && game->leftGunner.health > 0)
  {
    game->nowFireLeft = clock();
    float diff = ((float)(game->nowFireLeft - game->lastFireLeft) / 1000000.0F ) * 1000;
    if(diff > 1.00)
    {
        //addBullet(7.0, 230.0, &bulletsLeft);
        addBullet(game->leftGunner.x+4, 230.0, &bulletsLeft);
        game->lastFireLeft = game->nowFireLeft;
    };
  }
  else
  {
    game->leftGunner.gunFired = 0;
  }

  // Fire Main Gunner
  //if(game->mainGunner.selected == 1 && state[SDL_SCANCODE_SPACE])
  if(game->mainGunner.selected == 1 && state[SDL_SCANCODE_SPACE] && game->mainGunner.health > 0)
  {
    game->nowFire = clock();
    float diff = ((float)(game->nowFire - game->lastFire) / 1000000.0F ) * 1000;
    if(diff > 0.15)
    {
        addBullet(163.0, 230.0, &bullets);
        game->lastFire = game->nowFire;
    };
  }
  else
  {
    game->mainGunner.gunFired = 0;
  }

  // Fire Right Gunner
  //if(game->rightGunner.selected == 1 && state[SDL_SCANCODE_SPACE])
  if(game->rightGunner.selected == 1 && state[SDL_SCANCODE_SPACE] && game->rightGunner.health > 0)
  {
    game->nowFireRight = clock();
    float diff = ((float)(game->nowFireRight - game->lastFireRight) / 1000000.0F ) * 1000;
    if(diff > 1.00)
    {
        //addBullet(316.0, 230.0, &bulletsRight);
        addBullet(game->rightGunner.x+4, 230.0, &bulletsRight);
        game->lastFireRight = game->nowFireRight;
    };
  }
  else
  {
    game->rightGunner.gunFired = 0;
  }

  //---------------------------- Enemy Spawn ----------------------------//
  //Kraut Spawn
  game->nowkrtSpawn = clock();
  float diff = ((float)(game->nowkrtSpawn - game->lastkrtSpawn) / 1000000.0F ) * 1000;
  if(diff > 1.00)
  {
      int randomNum = rand();
      game->lastkrtSpawn = game->nowkrtSpawn;

      //DEBUG spawn additional kraut
      if(randomNum % 2 == 0)
        spawnKraut(320.0, 160.0);
      else
        spawnKraut(1.0, 120.0);
  };

  //Tank Spawn
  game->nowTankSpawn = clock();
  float diffTank = ((float)(game->nowTankSpawn - game->lastTankSpawn) / 1000000.0F ) * 1000;
  if(diffTank > 10.0)
  {
    game->lastTankSpawn = game->nowTankSpawn;
    spawnTank(320.0, 34.0);
  }

  //---------------------------- Enemy Behavior ----------------------------//

  //Kraut Solider Behavior
  for(int i=0; i<MAX_KRAUTS;i++) if(krauts[i])
  {
    int randomNum = rand() % 100;

    //Left Gunner Fire Check
    if(krauts[i]->x > game->leftGunner.x-25 && krauts[i]->x < game->leftGunner.x+25)
    {
        //Fire Test
        if(krauts[i]->isFire == 0){
            if(randomNum <= 25){
                krauts[i]->willFire = 1;
                krauts[i]->isFire = 1;
            }
        }
        krauts[i]->isFire = 1;
        //Fire Round
        if(krauts[i]->willFire == 1){
            krauts[i]->dx = 0.5;
            if(krauts[i]->x == game->leftGunner.x){
                addBullet(krauts[i]->x, krauts[i]->y, &germanBullets);
            };
        };
    }
    //Main Gunner Fire Check
    else if(krauts[i]->x > game->mainGunner.x-25 && krauts[i]->x < game->mainGunner.x+25)
    {
        //Fire Test
        if(krauts[i]->isFire == 0){
            if(randomNum <= 25){
                krauts[i]->willFire = 1;
                krauts[i]->isFire = 1;
            };
        };
        krauts[i]->isFire = 1;
        //Fire Round
        if(krauts[i]->willFire == 1){
            krauts[i]->dx = 2.0;
            if(krauts[i]->x == game->mainGunner.x){
                addBullet(krauts[i]->x, krauts[i]->y, &germanBullets);
            };
        };
    }
    //Right Gunner Fire Check
    else if(krauts[i]->x > game->rightGunner.x-25 && krauts[i]->x < game->rightGunner.x+25)
    {
        //Fire Test
        if(krauts[i]->isFire == 0){
            if(randomNum <= 25){
                krauts[i]->willFire = 1;
                krauts[i]->isFire = 1;
            }
        }
        krauts[i]->isFire = 1;
        //Fire Round
        if(krauts[i]->willFire == 1){
            krauts[i]->dx = 0.5;
            if(krauts[i]->x == game->rightGunner.x){
                addBullet(krauts[i]->x, krauts[i]->y, &germanBullets);
            };
        };
    }
    //Reset test in between gunners
    else
    {
        krauts[i]->inRange = 0;
        krauts[i]->isFire = 0;
        krauts[i]->willFire = 0;
        krauts[i]->dx = 1.0;
    }
  };

  //Tank Behavior
  //TODO!

  //---------------------------- Movement (projectile and characters) ----------------------------//
  //kraut movement/off-screen
  for(int i=0; i<MAX_KRAUTS;i++) if(krauts[i])
  {
     //move kraut left or right
     if(krauts[i]->y == 160.00)
        krauts[i]->x -= krauts[i]->dx;
     else if(krauts[i]->y == 120.00)
        krauts[i]->x += krauts[i]->dx;

     if(krauts[i]->x < -20.0 || krauts[i]->x > 340.0)
     {
        killKraut(i);
     }
  };

  //tank movement/off-screen
  for(int i=0; i<MAX_TANKS;i++) if(tanks[i])
  {
    tanks[i]->x -= tanks[i]->dx;
    if(tanks[i]->x < -20.0 || tanks[i]->x > 340.0)
    {
        killTank(i);
    }
  };

  //bullet left movement/off-screen
  for(int i=0; i<MAX_BULLETS;i++) if(bulletsLeft[i])
  {
     bulletsLeft[i]->y -= bulletsLeft[i]->dx;
     //bulletsLeft[i]->x += bulletsLeft[i]->dx;
     if(bulletsLeft[i]-> y < -10 || bulletsLeft[i]-> x > 330)
        removeBullet(i, &bulletsLeft);
  };

  //bullet movement/off-screen
  for(int i=0; i<MAX_BULLETS;i++) if(bullets[i])
  {
     bullets[i]->y -= bullets[i]->dx;
     if(bullets[i]->y < -10)
        removeBullet(i, &bullets);
  };

  //bullet right movement/off-screen
  for(int i=0; i<MAX_BULLETS;i++) if(bulletsRight[i])
  {
     bulletsRight[i]->y -= bulletsRight[i]->dx;
     //bulletsRight[i]->x -= bulletsRight[i]->dx;
     if(bulletsRight[i]-> y < -10 || bulletsRight[i]-> x < -10)
        removeBullet(i, &bulletsRight);
  };

  //DEBUG german bullet right movement/off-screen
  for(int i=0; i<MAX_BULLETS;i++) if(germanBullets[i])
  {
     germanBullets[i]->y += germanBullets[i]->dx;
     if(germanBullets[i]->y > 250)
        removeBullet(i, &germanBullets);
  };

  //---------------------------- Collision Detection ----------------------------//
  //Shoot kraut collide
  for(int r = 0; r < MAX_KRAUTS; r++)
  {
    if(krauts[r])
    {
      for(int k=0; k < MAX_BULLETS;k++)
      {
         //left bullet collide
         if(bulletsLeft[k])
         {
            if(collide2d(bulletsLeft[k]->x, bulletsLeft[k]->y, krauts[r]->x, krauts[r]->y, 2, 2, 20, 20))
            {
               krauts[r]->dead = 1;
               removeBullet(k, &bulletsLeft);
            }
         }
         //main bullet collide
         if(bullets[k])
         {
            if(collide2d(bullets[k]->x, bullets[k]->y, krauts[r]->x, krauts[r]->y, 2, 2, 20, 20))
            {
               krauts[r]->dead = 1;
               removeBullet(k, &bullets);
            }
         }
         //right bullet collide
         if(bulletsRight[k])
         {
            if(collide2d(bulletsRight[k]->x, bulletsRight[k]->y, krauts[r]->x, krauts[r]->y, 2, 2, 20, 20))
            {
               krauts[r]->dead = 1;
               removeBullet(k, &bulletsRight);
            }
         }
      }
    }
  }

  for(int r = 0; r < MAX_KRAUTS; r++)
  {
    if(krauts[r])
    {
        if(krauts[r]->dead == 1)
        {
            killKraut(r);
        }
    }
  }

  //shoot tank collide
  for(int r = 0; r < MAX_TANKS; r++)
  {
    if(tanks[r])
    {
        for(int k=0; k < MAX_BULLETS;k++)
        {
            //left bullet collide
            if(bulletsLeft[k])
            {
                if(collide2d(bulletsLeft[k]->x, bulletsLeft[k]->y, tanks[r]->x, tanks[r]->y, 2, 2, 60, 20))
                {
                    tanks[r]->life -= 1;
                    removeBullet(k, &bulletsLeft);
                }
            }

              //main bullet collide
             if(bullets[k])
             {
                if(collide2d(bullets[k]->x, bullets[k]->y, tanks[r]->x, tanks[r]->y, 2, 2, 60, 20))
                {
                   tanks[r]->life -= 1;
                   removeBullet(k, &bullets);
                }
             }

             //right bullet collide
            if(bulletsRight[k])
            {
                if(collide2d(bulletsRight[k]->x, bulletsRight[k]->y, tanks[r]->x, tanks[r]->y, 2, 2, 60, 20))
                {
                    tanks[r]->life -= 1;
                    removeBullet(k, &bulletsRight);
                }
            }
        }
    }
  }

  for(int r = 0; r < MAX_TANKS; r++)
  {
    if(tanks[r])
    {
        if(tanks[r]->life <= 0)
        {
            killTank(r);
        }
    }
  }

  //DEBUG solider shoot collide

  //Left Gunner Collision Check
  for(int r = 0; r < MAX_BULLETS; r++){
    if(germanBullets[r]){
        if(collide2d(germanBullets[r]->x, germanBullets[r]->y, game->leftGunner.x, game->leftGunner.y, 2, 2, 8, 8)){
            if(game->leftGunner.selected == 1){
                    printf("LEFT gunner hit\n");
                    game->leftGunner.health -= 1;
            };
            removeBullet(r, &germanBullets);
        };
    }
  };
  //Main Gunner Collision Check
  for(int r = 0; r < MAX_BULLETS; r++){
    if(germanBullets[r]){
        //Main Gunner Collision
        if(collide2d(germanBullets[r]->x, germanBullets[r]->y, game->mainGunner.x, game->mainGunner.y, 2, 2, 8, 8)){
            if(game->mainGunner.selected == 1){
                    printf("MAIN gunner hit\n");
                    game->mainGunner.health -= 1;
            };
            removeBullet(r, &germanBullets);
        };
    }
  };
  //Right Gunner Collision Check
  for(int r = 0; r < MAX_BULLETS; r++){
    if(germanBullets[r]){
        if(collide2d(germanBullets[r]->x, germanBullets[r]->y, game->rightGunner.x, game->rightGunner.y, 2, 2, 8, 8)){
            if(game->rightGunner.selected == 1){
                printf("RIGHT gunner hit\n");
                game->rightGunner.health -= 1;
            };
            removeBullet(r, &germanBullets);
        };
    }
  };


  //DEBUG collision calibration
  /*if(collide2d(reticule->x, reticule->y, collider->x, collider->y, 2, 2, 20, 20))
  {
      printf("HIT HIT!\n");
  }*/

  //---------------------------- End Event ----------------------------//
  return done;
};
