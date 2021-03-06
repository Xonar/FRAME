/*
 * File :
 *      ./FRAME.cpp
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
#include "Engine/FontEngine.h"
#include "Engine/RenderEngine.h"
#include "Engine/ModelEngine.h"
#include "Engine/LightEngine.h"
#include "Graphics/Graphics.h"
#include "Game.h"
#include "Lib/FGLext.h"
#include "Time/Time.h"
#include "Lib/Log.h"
#include "Shader/ShaderManager.h"
#include "Keyboard/Keyboard.h"
#include "Mouse/Mouse.h"

//Definitions of Global Variables
bool gGameOn = true;
FWindow *gWindow;
FFontEngine *gFontEngine;
FRenderEngine* gRenderEngine;
FModelEngine* gModelEngine;
FLightEngine* gLightEngine;
FFont *gFontConsole;
FKeyboard *gKeyboard;
FMouse *gMouse;
bool gDisplayFrameStats = true;
FTime gFrameTimeCur = {0, 0};
FTime gFrameTimePrev = {0, 0};
FTime gFrameTimeDelta = {0, 0};
FShaderManager* gShaderManager;

int main(int argc, char *argv[])
{
  //Display Command Line Arguments
  std::cout << "Arguments Passed to Program: " << std::endl;
  for(int i = 0; i < argc; i++)
    std::cout << "\t " << i << ": " << argv[i] << std::endl;

  //TODO Parse Arguments

  //Init SDL
  FWindow window("FRAME Engine Test");

  //If SDL/OpenGL Init Failed
  if(window.Init())
  {
    gLoge << "Failed startup!" << std::endl;
    
    //Reset Terminal Colours
    #ifdef COLOUR_TERMINAL
      std::cout << TERM_STATE_RESET << std::flush;
      std::cerr << TERM_STATE_RESET << std::flush;
    #endif //COLOUR_TERMINAL

    //Failed
    return 1; 
  }

  gWindow = &window;

  //Init OpenGL
  initGLFunction();

#ifdef DEBUG
  //Force Debug Messages
  glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, 0, GL_TRUE);

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

  //Init Shader Manager
  gShaderManager = new FShaderManager();
  
  //Init SDL Font Engine
  TTF_Init();
  
  //Init FontEngine
  gFontEngine = new FFontEngine();

  gFontConsole = new FFont();
  gFontConsole->createFromTTF("Assets/CosmicSansNeueMono.ttf", 14);

  gFontEngine->addFont(gFontConsole);
  
  //Init ModelEngine
  gModelEngine = new FModelEngine();

  //Init RenderEngine
  gRenderEngine = new FRenderEngine();

  //Init LightEngine
  gLightEngine = new FLightEngine();

  //Init FTime
  initTime();

  initializeGame();

  gRenderEngine->Init();

  //Init IO
  gKeyboard = new FKeyboard();
  gMouse = new FMouse();

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

    //Update IO
    gKeyboard->updateState();
    gMouse->updateState();

    //Update Time
    gFrameTimePrev = gFrameTimeCur;
    gFrameTimeCur = FGetTime();
    gFrameTimeDelta = gFrameTimeCur - gFrameTimePrev;
    
    //Update
    updateGame();

    //Render
    window.Render();

    //All GL Error should be handled immediately and the GL error flag set to GL_NO_ERROR
    GL_ERROR_ASSERT();
  }

  //Reset Terminal Colours
#ifdef COLOUR_TERMINAL
  std::cout << TERM_STATE_RESET << std::flush;
  std::cerr << TERM_STATE_RESET << std::flush;
#endif //COLOUR_TERMINAL

  return 0;
}
