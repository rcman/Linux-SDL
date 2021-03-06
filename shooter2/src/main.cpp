/*This source code copyrighted by Lazy Foo' Productions (2004-2009) and may not
be redestributed without written permission.*/

//The headers
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "main.h"

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

void clean_up()
{
    // free the memory we allocated in Gameinit()

    if (tileset) { SDL_FreeSurface(tileset); }

    // event is not an array, so we do not use the array-form of the delete operator:
    if (event) { delete event; }
    // Delete Player


}

int main( int argc, char* args[] )
{
    //Quit flag
    bool quit = false;

    //Initialize
    if (!Gameinit())
    {
        return 1;
    }



    //While the user hasn't quit
    while(!quit)
    {
        //While there's events to handle
        while( SDL_PollEvent( event ) )
        {
            //If the user has Xed out the window
            if( event->type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }

            // the user hits ESC
           // if (event->type==SDL_KEYDOWN &&(event->key.keysym.sym==SDLK_ESCAPE)){quit=true;}
            switch(event->type)
            {
		        // a key was pressed
				case SDL_KEYDOWN:
				{
					// what key is down
					switch(event->key.keysym.sym)
					{
						case SDLK_ESCAPE:
						{
							// stop the engine
							quit=true;
						} break;

						case 'w':
						case 'W':
						case SDLK_UP:
						{
							motionButtonDown[MOTIONBUTTON_UP] = true;
						} break;

						case 's':
						case 'S':
						case SDLK_DOWN:
						{
							motionButtonDown[MOTIONBUTTON_DOWN] = true;
						} break;

						case 'a':
						case 'A':
						case SDLK_LEFT:
						{
							motionButtonDown[MOTIONBUTTON_LEFT] = true;
						} break;
                       	case 'd':
						case 'D':
						case SDLK_RIGHT:
						{
							motionButtonDown[MOTIONBUTTON_RIGHT] = true;
						} break;

						default: break;
						case SDLK_LCTRL:
						{
                            actionButtonDown[ACTIONBUTTON_A] = true;
						} break;
					} // end switch
				} break;

				// a key was released
				case SDL_KEYUP:
				{
					// what key is up
					switch(event->key.keysym.sym)
					{
						case 'w':
						case 'W':
						case SDLK_UP:
						{
							motionButtonDown[MOTIONBUTTON_UP] = false;
						} break;

						case 's':
						case 'S':
						case SDLK_DOWN:
						{
							motionButtonDown[MOTIONBUTTON_DOWN] = false;
						} break;

						case 'a':
						case 'A':
						case SDLK_LEFT:
						{
							motionButtonDown[MOTIONBUTTON_LEFT] = false;
						} break;
                        case 'd':
						case 'D':
						case SDLK_RIGHT:
						{
							motionButtonDown[MOTIONBUTTON_RIGHT] = false;
						} break;
                        default: break;
						case SDLK_LCTRL:
						{
                                actionButtonDown[ACTIONBUTTON_A] = false;
						} break;

					}
				} break;
            }



        }
        DrawMainMap();

        check_input();
        movebullets();
        check_collision();
        enemyexplodecheck();
        //drawenemies();
        moveplayer();
        SDL_Flip(screen);
        SDL_Delay(20);
    }

    //Free the images and quit SDL
    clean_up();

    return 0;
}
