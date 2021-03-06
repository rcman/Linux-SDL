
#include <SDL2/SDL.h>
#include "main.h"

SDL_Surface* screen = 0;
SDL_Surface* tileset = 0;

SDL_Surface* man = 0;
SDL_Rect* manA;

SDL_Surface* enemy = 0;
SDL_Rect* enemy1;

MyPlayer* player = 0;
Shipshots* shots = 0;

SDL_Event* 	event = 0;

bool motionButtonDown[4] = {false, false, false, false};

Shipshots savedshots[MAX_SHOTS];
Enemyspots savedenemy[MAX_ENEMIES];


bool actionButtonDown[1];

//The event structure

bool Gameinit()
{
    // initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }
    atexit(SDL_Quit);

    // set up the screen
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_DOUBLEBUF);

    // if there was an error in setting up the screen
    if (!screen)
    {
        return false;
    }

    if (!init_player()){ return false; };


    //Set the window caption
    SDL_WM_SetCaption( "Franco Gaetan's Shooter Game Demo ", 0 );

    // create the sdl event
    event = new SDL_Event;


    // load the files
    if (!load_files())
    {
        return false;
    }

    // load man files
    if (!load_man())
    {
        return false;
    }


//struct Shipshots
//{
//        int x,y;
//        int h,w;
//        int velx,vely;
//        bool shotalive;
//};




    int i;



    for (i=0;i<MAX_SHOTS;i++)
    {
        savedshots[i].shotalive = false;
        savedshots[i].x = 0;
        savedshots[i].y = 0;
        savedshots[i].h = 32;
        savedshots[i].w = 32;
        savedshots[i].velx = 0;
        savedshots[i].vely = 0;

    }

    for (i=0;i<MAX_ENEMIES;i++)
    {
        savedenemy[i].x = 10 + rand() % (500 - 10 );
        savedenemy[i].y = 10 + rand() % (500 - 10 );
        savedenemy[i].h = 32;
        savedenemy[i].w = 32;
        savedenemy[i].velx = 0;
        savedenemy[i].vely = 0;
        savedenemy[i].enemyalive = true;
        savedenemy[i].collisiondetected = false;
        savedenemy[i].animnumber = 0;



};

extern Enemyspots savedenemy[MAX_ENEMIES];

    // plane is 704 and 109
    // 32 * 4 on Y = 128
    // 24 * 32 = 768

    manA = new SDL_Rect[18];            // Main player needs to be changed
    enemy1 = new SDL_Rect[18];          // Enemy array

    player->animnumber = 0;
    player->y = 650;
    player->x = 599;
    player->velx = 9;
    player->vely = 9;
    player->firingdelay =3;
    player->firingcounter = 0;
    player->shotsfired = 0;


    manA[0].x = 697;
    manA[0].y = 103;
    manA[0].w = 98;
    manA[0].h = 98;

    manA[1].x = 37;
    manA[1].y = 169;
    manA[1].w = 32;
    manA[1].h = 32;

    enemy1[0].x = 4;  // Enemy Ship 1
    enemy1[0].y = 4;
    enemy1[0].w = 32;
    enemy1[0].h = 32;

    enemy1[1].x = 70;  // Enemy Ship Explosion 1
    enemy1[1].y = 169;
    enemy1[1].w = 32;
    enemy1[1].h = 32;

    enemy1[2].x = 102;  // Enemy Ship Explosion 2
    enemy1[2].y = 169;
    enemy1[2].w = 32;
    enemy1[2].h = 32;

    enemy1[3].x = 134;  // Enemy Ship Explosion 3
    enemy1[3].y = 169;
    enemy1[3].w = 32;
    enemy1[3].h = 32;

    enemy1[4].x = 166;  // Enemy Ship Explosion 4
    enemy1[4].y = 169;
    enemy1[4].w = 32;
    enemy1[4].h = 32;

    enemy1[5].x = 198;  // Enemy Ship Explosion 5
    enemy1[5].y = 169;
    enemy1[5].w = 32;
    enemy1[5].h = 32;

    enemy1[6].x = 230;  // Enemy Ship Explosion 6
    enemy1[6].y = 169;
    enemy1[6].w = 32;
    enemy1[6].h = 32;

	// clear screen to black
	SDL_FillRect(screen, 0, 0);


	return true;
}

