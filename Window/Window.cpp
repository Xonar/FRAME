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
  this->window = SDL_CreateWindow(this->title.c_str(),this->x,this->y,width,height,mode);
  this->context = SDL_GL_CreateContext(this->window);

  //Set Viewport
  glViewport( 0.f, 0.f, this->width, this->height);

  //Initialize Clear Color
  glClearColor( 0.f, 0.f, 0.f, 1.f );

  //Get GL Variables
  SDL_GL_GetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, &this->glMajorVersion );
  SDL_GL_GetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, &this->glMinorVersion );

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
