/*
 *  File : Main.cpp
 *
 *  Author : Xonar < Paul le Roux >
 *
 *  Program Entry for FRAME and Program Loop
 *
 */

#include <SDL2/SDL.h>

#include "Global.h"
#include "Window/Window.h"

int main()
{
  //Init SDL
  FWindow window("FRAME Engine Test");

  window.Init();

  SDL_Delay(2000);

  //Game Loop
  while(gGameOn)
  {
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
      switch(event.type)
      {
        case SDL_QUIT:
        gGameOn = false;
        break;
      }
    }

    window.Render();
  }

  return 0;
}
