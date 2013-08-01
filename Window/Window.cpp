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

#include <SDL2/SDL_opengl.h>

#include <iostream>

FWindow::FWindow(std::string title)
{
  //Initialize Window with default settings
  this->title = title;
}

int FWindow::Init()
{
  //Create Window
  this->window = SDL_CreateWindow(this->title.c_str(),this->x,this->y,width,height,mode);

  //Create Dummy Context
  this->context = SDL_GL_CreateContext(this->window);
 
  //Get OpenGL Version
  const GLubyte* sGLVersion =  glGetString(GL_VERSION);

  this->glMajorVersion = (sGLVersion[0]-'0')*10;
  this->glMajorVersion += (sGLVersion[2]-'0');
  
  //Desotry Context as its not need any more
  SDL_GL_DeleteContext(this->context);

  if(this->glMajorVersion >= 41)
  {
    this->glMajorVersion = 4;
    this->glMinorVersion = 2;
  }
  else if(this->glMajorVersion >= 33)
  {
    this->glMajorVersion = 3;
    this->glMinorVersion = 3;
  }
  else
  {
    std::cerr << "Can't create OpenGL 3.3+ Context! ( Can only create " 
              << glMajorVersion/10 << "." << glMajorVersion%10 << ")" << std::endl;

    //Exit
    SDL_DestroyWindow( this->window);
    
    return 1;
  }

  //Create Context
  SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, this->glMajorVersion );
  SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, this->glMinorVersion );

  this->context = SDL_GL_CreateContext( this->window);

  //Set Viewport
  glViewport( 0.f, 0.f, this->width, this->height);

  //Initialize Clear Color
  glClearColor( 0.f, 0.f, 0.f, 1.f );

  //Start Message
  std::cout << "Intialized Window : \"" << title << "\"" << std::endl;
  std::cout << "\tOpengl Major Version : " << this->glMajorVersion << std::endl; 
  std::cout << "\tOpengl Minor Version : " << this->glMinorVersion << std::endl; 

  return 0;
}

int FWindow::Render()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  SDL_GL_SwapWindow(this->window);

  return 0;
}
