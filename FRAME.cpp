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
#include "Game.h"
#include "Lib/FGLext.h"

//Definitions of Global Variables
bool gGameOn = true;
FWindow *gWindow;


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

  gWindow = &window;

  //Init OpenGL
  initGLFunction();

  //Init SDL Font Engine
  TTF_Init();

  initializeGame();

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

    //All GL Error should be handled immediately and the GL error flag set to GL_NO_ERROR
    GL_ERROR_ASSERT();
  }

  return 0;
}
