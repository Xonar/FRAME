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
#include "Time/Time.h"
#include "Lib/Log.h"

//Definitions of Global Variables
bool gGameOn = true;
FWindow *gWindow;
FFontEngine *gFontEngine;
FFont *gFontConsole;
bool gDisplayFrameStats = true;

int main(int argc, char *argv[])
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
  
  //Init FontEngine
  gFontEngine = new FFontEngine();

  gFontConsole = new FFont();
  gFontConsole->createFromTTF("Assets/UbuntuMono-R.ttf", 14);

  gFontEngine->addFont(gFontConsole);

#ifdef DEBUG
  //Start Debug Output
  if(glIsExtensionSupported("GL_KHR_debug"))
  {
    gLogv << "Using GL_KHR_debug to log GL error messages" << std::endl;
    glDebugMessageCallback(glDebugMessageCallbackFunction, NULL);
  }
  else if(glIsExtensionSupported("GL_ARB_debug_output"))
  {
    gLogv << "Using GL_ARB_debug_output to log GL error messages" << std::endl;
    glDebugMessageCallbackARB(glDebugMessageCallbackFunction, NULL);
  }
  else if(glIsExtensionSupported("GL_AMD_debug_output"))
  {
    gLogv << "Using GL_AMD_debug_output to log GL error messages" << std::endl;
    glDebugMessageCallbackAMD(glDebugMessageCallbackFunctionAMD, NULL);
  }
  else
  {
    gLogw << "GL_KHR_debug,GL_ARB_debug_output and GL_AMD_debug_output not supported!" << std::endl;
    gLogw << "No GL Error messages will be displayed!" << std::endl;
  }
#endif //DEBUG
  
  GL_ERROR_ASSERT();

  //Init FTime
  initTime();

  initializeGame();

  GL_ERROR_ASSERT();

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
    
    //Render
    window.Render();

    //All GL Error should be handled immediately and the GL error flag set to GL_NO_ERROR
    GL_ERROR_ASSERT();
  }

  return 0;
}
