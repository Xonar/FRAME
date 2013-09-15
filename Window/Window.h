/*
 * File :
 *      ./Window/Window.h
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      The Window class is a handler for the window
 */

#ifndef _F_H_WINDOW_
#define _F_H_WINDOW_

#include <string>

#include <SDL2/SDL.h>

class FWindow
{
private:
  //SDL Window
  std::string title = "NULL";
  int width=640;
  int height=480;
  int bpp=32;
  int mode=SDL_WINDOW_OPENGL;
  
  int x=100;
  int y=100;

  //Handles
  SDL_Window *window = NULL;
  SDL_GLContext context = NULL;

  //OpenGL
  int glMajorVersion;
  int glMinorVersion;

public:
  FWindow(std::string title);
  
  int Init();

  int Render();

  int getOpenGLVersion() { return glMajorVersion * 10 + glMinorVersion; }
};

#endif // _F_H_WINDOW_
