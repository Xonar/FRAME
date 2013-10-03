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
#include "../Global.h"

#include <iostream>

//Vertex Array objects
GLuint fglVertexArrayText = 0;
GLuint fglVertexArray2 = 0;
GLuint fglVertexArray3 = 0;

GLint glInitFGLext()
{
  //Init Vertex Array Objects
  glGenVertexArrays(1, &fglVertexArray3);
  glBindVertexArray(fglVertexArray3);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(FVertex2), (GLvoid*) 0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(FVertex2), (GLvoid*) (sizeof(float) * 3) );
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(FVertex2), (GLvoid*) (sizeof(float) * 5) );
  glEnableVertexAttribs(F_VERTEX_3);

  glGenVertexArrays(1, &fglVertexArray2);
  glBindVertexArray(fglVertexArray2);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(FVertex2), (GLvoid*) 0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(FVertex2), (GLvoid*) (sizeof(float) * 3) );
  glEnableVertexAttribs(F_VERTEX_2);
      
  glGenVertexArrays(1, &fglVertexArrayText);
  glBindVertexArray(fglVertexArrayText);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(FTextVertex), (GLvoid*) 0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(FTextVertex), (GLvoid*) (sizeof(float) * 3) );
  glEnableVertexAttribs(F_VERTEX_TEXT);
  
  //Don't start with any binded vao
  glBindVertexArray(0);

  return 0;
}

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

const GLchar* glDebugSourceString(GLenum source)
{
  switch(source)
  {
    case GL_DEBUG_SOURCE_API_ARB: return "GL_DEBUG_SOURCE_API";
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB: return "GL_DEBUG_SOURCE_WINDOW_SYSTEM";
    case GL_DEBUG_SOURCE_SHADER_COMPILER_ARB: return "GL_DEBUG_SOURCE_SHADER_COMPILER";
    case GL_DEBUG_SOURCE_THIRD_PARTY_ARB: return "GL_DEBUG_SOURCE_THIRD_PARTY";
    case GL_DEBUG_SOURCE_APPLICATION_ARB: return "GL_DEBUG_SOURCE_APPLICATION";
    case GL_DEBUG_SOURCE_OTHER_ARB: return "GL_DEBUG_SOURCE_OTHER";
    default: return "glDebugSourceString: INVALID_ENUM";
  }
}

const GLchar* glDebugTypeString(GLenum type)
{
  switch(type)
  {
    case GL_DEBUG_TYPE_ERROR_ARB: return "GL_DEBUG_TYPE_ERROR";
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB: return "GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR";
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB: return "GL_DEBUG_TYPE_UNDEFINED_BAHAVIOR";
    case GL_DEBUG_TYPE_PORTABILITY_ARB: return "GL_DEBUG_TYPE_PORTABILITY";
    case GL_DEBUG_TYPE_PERFORMANCE_ARB: return "GL_DEBUG_TYPE_PERFORMANCE";
    case GL_DEBUG_TYPE_OTHER_ARB: return "GL_DEBUG_TYPE_OTHER";
    default: return "glDebugTypeString: INVALID_ENUM";
  }
}

const GLchar* glDebugSeverityString(GLenum severe)
{
  switch(severe)
  {
    case GL_DEBUG_SEVERITY_HIGH_ARB: return "GL_DEBUG_SEVERITY_HIGH";
    case GL_DEBUG_SEVERITY_MEDIUM_ARB: return "GL_DEBUG_SEVERITY_MEDIUM";
    case GL_DEBUG_SEVERITY_LOW_ARB: return "GL_DEBUG_SEVERITY_LOW";
    default: return "glDebugSeverityString: INVALID_ENUM";
  }
}

GLvoid glDebugMessageCallbackFunction( GLenum source, GLenum type, GLuint id, GLenum severity,
                               GLsizei length, const GLchar* message, GLvoid* userParam)
{
  //Set Bold Red
  std::cerr << TERM_STATE_BOLD << TERM_COL_RED;

  std::cerr << "Source:   " << glDebugSourceString(source) << std::endl;
  std::cerr << "Type:     " << glDebugTypeString(type) << std::endl;
  std::cerr << "Severity: " << glDebugSeverityString(severity) << std::endl;
  std::cerr << "Message:  " << std::endl << "\t" << message << std::endl;
  
  //Reset Colour
  std::cerr << TERM_STATE_RESET << TERM_COL_DEFAULT;
}

GLvoid glBindVertexArrayFGL( FVertexEnum type )
{
  switch( type )
  {
    case F_VERTEX_3:
      glBindVertexArray(fglVertexArray3);
      break;
    case F_VERTEX_2:
      glBindVertexArray(fglVertexArray2);
      break;
    case F_VERTEX_TEXT:
      glBindVertexArray(fglVertexArrayText);
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
      glEnableVertexAttribArray(2);
    case F_VERTEX_2:
    case F_VERTEX_TEXT:
      glEnableVertexAttribArray(0);
      glEnableVertexAttribArray(1);
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
      glDisableVertexAttribArray(2);
    case F_VERTEX_2:
    case F_VERTEX_TEXT:
      glDisableVertexAttribArray(0);
      glDisableVertexAttribArray(1);
      break;
   default:
      std::cerr << "F_INVALID_ENUM" << std::endl;
  }
}
