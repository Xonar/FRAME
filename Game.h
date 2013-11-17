/*
 * File :
 *      ./Game/Game.h
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      This Header contains game specific instructions that does the initail loading and updates
 */

#ifndef _F_H_GAME_
#define _F_H_GAME_

#include <SDL2/SDL_opengl.h>

#include "Model/Model.h"
#include "GUI/Font.h"
#include "Shader/Shader.h"

GLint initializeGame();


GLvoid updateGame();

// TODO this function is only here in the testing phase 
// where all the objects isn't fully functional.
// All Entities will be responsible for their own drawing 
// once they are registered to the Rendering Piepline
GLvoid drawGame();

#endif //_F_H_GAME_
