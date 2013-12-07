/*
 * File :
 *      ./Window/Window.cpp
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      Definitions of ./Window/Window.h
 */

#include "Window.h"
#include "../Game.h"
#include "../Global.h"
#include "../Time/Time.h"

#include "../Lib/Log.h"

#include <SDL2/SDL_opengl.h>

#include <iostream>
#include <cstring>
#include <algorithm>

FWindow::FWindow(const std::string &title)
{
  //Initialize Window with default settings
  this->title = title;
}


int FWindow::Init()
{
  //Create Window
  this->window = SDL_CreateWindow(this->title.c_str(),this->x,this->y,width,height,mode);

  //Set SDL log lvl
#ifdef DEBUG
  SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
#endif

  //Check if Window was created succesfully
  if(!this->window)
  {
    gLoge << "Couldn't create SDL Window!" << std::endl;

    gLoge << "SDL Error : " << SDL_GetError() << std::endl;

    //Exit
    SDL_DestroyWindow( this->window);
    
    return 1;
  }
  
  //Create Dummy Context
  this->context = SDL_GL_CreateContext(this->window);

  //Check if Context was created succesfully
  if(!this->context)
  {
    gLoge << "Couldn't create OpenGL Context!" << std::endl;

    gLoge << "SDL Error : " << SDL_GetError() << std::endl;

    //Exit
    SDL_DestroyWindow( this->window);
    
    return 1;
  }

  glGetIntegerv(GL_MAJOR_VERSION, &this->glMajorVersion);
  glGetIntegerv(GL_MINOR_VERSION, &this->glMinorVersion);
 
  //Get OpenGL Version
  const GLubyte* sGLVersion =  glGetString(GL_VERSION);

  gLogv << "OpenGL Version String : " << sGLVersion << std::endl;

  //Desotry Context as it's not needed any more
  SDL_GL_DeleteContext(this->context);
  bool validGLVersion = true;

  if(this->glMajorVersion > 4 || (this->glMajorVersion == 4 && this->glMinorVersion >= 2) ) 
  {
    //If Tesselation and Tesselation Transoform feedback supported
    this->glMajorVersion = 4;
    this->glMinorVersion = 2;
  }
  else if( this->glMajorVersion == 4 || (this->glMajorVersion == 3 && this->glMinorVersion >= 3) )
  {
    //Target highest version of the form 3.x which MESA supports
    this->glMajorVersion = 3;
    this->glMinorVersion = 3;
  }
  else
  {
    validGLVersion = false;

    gLogw << "Can't create OpenGL 3.3+ Context! (Reported Version :  " 
              << glMajorVersion << "." << glMinorVersion << ")" << std::endl;

    gLogi << "Try and Create OpenGL 3.3 Context Anyway" << std::endl;

    this->glMajorVersion = 3;
    this->glMinorVersion = 3;
  }

  //Profile Mask
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  //Context Flags
  SDL_GL_SetAttribute( SDL_GL_CONTEXT_FLAGS, 0
#ifdef DEBUG
        | SDL_GL_CONTEXT_DEBUG_FLAG
#endif
        );

  //Create Context
  SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, this->glMajorVersion );
  SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, this->glMinorVersion );

  this->context = SDL_GL_CreateContext( this->window);

  if(!this->context)
  {
    gLoge << "Failed creating OpenGL Context!" << std::endl;

    //Exit
    SDL_DestroyWindow(this->window);
    
    return 1;
  }
  else if(!validGLVersion)
  {
    gLogi << "Context Creation reported succesful creation of 3.3 Context! Yay!" << std::endl;
  }

  //Set Default Viewport
  glViewport( 0.f, 0.f, this->width, this->height);

  //Initialize Clear Color
  glClearColor( 0.f, 0.f, 0.f, 1.f );

  //Start Message
  gLogi << "Intialized Window : \"" << title << "\"" << std::endl;
  gLogi << "\tOpengl Major Version : " << this->glMajorVersion << std::endl; 
  gLogi << "\tOpengl Minor Version : " << this->glMinorVersion << std::endl; 

  return 0;
}

int FWindow::Render() const
{
  static FTime minTime = { 1000, 0}, maxTime = {0,0};
  static int counter = 0;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //Render Game
  FTime startTime = FGetTime();
  drawGame();
  FTime endTime = FGetTime();

  FTime diffTime = endTime - startTime;
  minTime = std::min(minTime, diffTime);
  maxTime = std::max(diffTime, maxTime);

  //Draw FPS
  if(gDisplayFrameStats)
  {
    gFontConsole->drawText("TIME:", glm::vec2( 5, this->height - 5 - 14 - 0 ) );   
    gFontConsole->drawText("cur : " +  FTimeString(diffTime) , 
                            glm::vec2( 15, this->height - 5 - 14 - 12) );   
    gFontConsole->drawText("max : " + FTimeString(maxTime), 
                            glm::vec2( 15, this->height - 5 - 14 - 24) );   
    gFontConsole->drawText("min : " + FTimeString(minTime), 
                            glm::vec2( 15, this->height - 5 - 14 - 36) );

    if(counter>120)
    {
      counter = 0;
      maxTime = {0, 0};
      minTime = {1000, 0};
    }
    else
      counter++;
  }

  //Render Text
  gFontEngine->render();

  SDL_GL_SwapWindow(this->window);

  return 0;
}
