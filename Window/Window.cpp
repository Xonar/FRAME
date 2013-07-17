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

FWindow::FWindow(std::string title)
{
  //Initialize Window with default settings
  this->title = title;
}

int FWindow::Init()
{
  this->window = SDL_CreateWindow(this->title.c_str(),this->x,this->y,width,height,mode);
  this->context = SDL_GL_CreateContext(this->window);

  return 0;
}

int FWindow::Render()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  SDL_GL_SwapWindow(this->window);

  return 0;
}
