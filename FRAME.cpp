/*
 * File :
 *      ./Main.cpp
 *
 * Author : 
 *      Xonar <Paul le Roux>
 *
 * Description :
 *      Program Entry for FRAME and Program Loop
 *
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Global.h"
#include "Window/Window.h"

bool gGameOn = true;

int main()
{
  //Init SDL
  FWindow window("FRAME Engine Test");

  window.Init();

  //Init SDL Font Engine
  TTF_Init();

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
