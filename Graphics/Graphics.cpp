/*
 * File :
 *      ./Graphics/Graphics.cpp
 *
 * Author : 
 *      Xonar <Paul le Roux>
 *
 * Description :
 *      Graphics Functions
 */

#include "Graphics.h"

int initGLFunction()
{
  //Load Core OpenGL
  int result = FGL::Load_GL_Core();

  //Load OpenGL Extensions
  FGL::Load_GL_KHR_debug();
  FGL::Load_GL_ARB_debug_output();
  FGL::Load_GL_AMD_debug_output();

  return result;
}
