/*
 * File :
 *      ./Global.h
 *
 * Author : 
 *      Xonar <Paul le Roux>
 *
 * Description :
 *      Contains all global variables
 */

#ifndef _F_H_GLOBAL_
#define _F_H_GLOBAL_

#include <SDL2/SDL_opengl.h>
#include "Window/Window.h"

//FRAME
extern bool gGameOn;

//UNIFORM BLOCKS
const GLuint F_UNIFORM_BLOCK_CAMERA = 0;
const GLuint F_UNIFORM_BLOCK_MODEL = 1;
const GLuint F_UNIFORM_BLOCK_LIGHT = 2;

extern FWindow *gWindow;

#endif // _F_H_GLOBAL_
