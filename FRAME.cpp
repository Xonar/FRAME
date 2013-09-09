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

#include <iostream>

#include "Global.h"
#include "Window/Window.h"
#include "Graphics/Graphics.h"

bool gGameOn = true;

int main()
{
  //Init SDL
  FWindow window("FRAME Engine Test");

  //If SDL/OpenGL Init Failed
  if(window.Init())
  {
    std::cerr << "Failed startup!" << std::endl;
    
    //Failed
    return 1; 
  }

  //Init OpenGL
  initGLFunction();

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
