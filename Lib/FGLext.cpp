/*
 * File :
 *      ./Lib/FGLext.cpp
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      Definitions of ./Lib/FGLext.h
 */

#include "FGLext.h"
#include "../Graphics/Graphics.h"

#include <iostream>

const GLchar* glErrorString(GLenum err)
{
  switch(err)
  {
    case GL_NO_ERROR: return "GL_NO_ERROR";
    case GL_INVALID_ENUM: return "GL_INVALID_ENUM";
    case GL_INVALID_VALUE: return "GL_INVALID_VALUE";
    case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
    case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
    case GL_OUT_OF_MEMORY: return "GL_OUT_OF_MEMORY";
    case GL_STACK_UNDERFLOW: return "GL_STACK_UNDERFLOW";
    case GL_STACK_OVERFLOW: return "GL_STACK_OVERFLOW";
    default: return "glErrorString: INVALID_ENUM";
  }
}


GLvoid glVertexAttribPointers( FVertexEnum type )
{
  switch( type )
  {
    case F_VERTEX_3:
      glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(FVertex2), (GLvoid*) 0);
      glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(FVertex2), (GLvoid*) (sizeof(float) * 3) );
      glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(FVertex2), (GLvoid*) (sizeof(float) * 6) );
      glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(FVertex2), (GLvoid*) (sizeof(float) * 8) );
      break;
    case F_VERTEX_2:
      glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(FVertex2), (GLvoid*) 0);
      glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(FVertex2), (GLvoid*) (sizeof(float) * 3) );
      glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(FVertex2), (GLvoid*) (sizeof(float) * 5) );
      break;
    case F_VERTEX_TEXT:
      glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(FTextVertex), (GLvoid*) 0);
      glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(FTextVertex), (GLvoid*) (sizeof(float) * 2) );
      glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(FTextVertex), (GLvoid*) (sizeof(float) * 4) );
      break;
    default:
      std::cerr << "F_INVALID_ENUM" << std::endl;

  }
}

GLvoid glEnableVertexAttribs( FVertexEnum type )
{
  switch( type )
  {
    case F_VERTEX_3:
      glEnableVertexAttribArray(3);
    case F_VERTEX_2:
    case F_VERTEX_TEXT:
      glEnableVertexAttribArray(0);
      glEnableVertexAttribArray(1);
      glEnableVertexAttribArray(2);
      break;
   default:
      std::cerr << "F_INVALID_ENUM" << std::endl;
  }
}

GLvoid glDisableVertexAttribs( FVertexEnum type )
{
  switch( type )
  {
    case F_VERTEX_3:
      glDisableVertexAttribArray(3);
    case F_VERTEX_2:
    case F_VERTEX_TEXT:
      glDisableVertexAttribArray(0);
      glDisableVertexAttribArray(1);
      glDisableVertexAttribArray(2);
      break;
   default:
      std::cerr << "F_INVALID_ENUM" << std::endl;
  }
}
