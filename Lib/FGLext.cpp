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
#include "Log.h"

#include <set>

const GLchar* glErrorString(const GLenum err)
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

const GLchar* glDebugSourceString(const GLenum source)
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

const GLchar* glDebugCategoryAMDString(const GLenum category)
{
  switch(category)
  {
    case GL_DEBUG_CATEGORY_API_ERROR_AMD: return "GL_DEBUG_CATEGORY_API_ERROR";
    case GL_DEBUG_CATEGORY_WINDOW_SYSTEM_AMD: return "GL_DEBUG_CATEGORY_WINDOW_SYSTEM";
    case GL_DEBUG_CATEGORY_DEPRECATION_AMD: return "GL_DEBUG_CATEGORY_DEPRECATION";
    case GL_DEBUG_CATEGORY_UNDEFINED_BEHAVIOR_AMD: return "GL_DEBUG_CATEGORY_UNDEFINED_BEHAVIOR";
    case GL_DEBUG_CATEGORY_PERFORMANCE_AMD: return "GL_DEBUG_CATEGORY_PERFORMANCE";
    case GL_DEBUG_CATEGORY_SHADER_COMPILER_AMD: return "GL_DEBUG_CATEGORY_SHADER_COMPILER";
    case GL_DEBUG_CATEGORY_APPLICATION_AMD: return "GL_DEBUG_CATEGORY_APPLICATION";
    case GL_DEBUG_CATEGORY_OTHER_AMD: return "GL_DEBUG_CATEGORY_OTHER";
    default: return "gldebugCategoryAMDString: INVALID ENUM";
  }
}

const GLchar* glDebugTypeString(const GLenum type)
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

const GLchar* glDebugSeverityString(const GLenum severe)
{
  switch(severe)
  {
    case GL_DEBUG_SEVERITY_HIGH_ARB: return "GL_DEBUG_SEVERITY_HIGH";
    case GL_DEBUG_SEVERITY_MEDIUM_ARB: return "GL_DEBUG_SEVERITY_MEDIUM";
    case GL_DEBUG_SEVERITY_LOW_ARB: return "GL_DEBUG_SEVERITY_LOW";
    default: return "glDebugSeverityString: INVALID_ENUM";
  }
}

const GLchar* glFramebufferCompleteString(const GLenum complete)
{
  switch(complete)
  {
    case GL_FRAMEBUFFER_UNDEFINED: return "GL_FRAMEBUFFER_UNDEFINED";
    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT: return "GL_FRAMEBUFFER_INCOMPLETE";
    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: return "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT";
    case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER: return "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER";
    case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER: return "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER";
    case GL_FRAMEBUFFER_UNSUPPORTED: return "GL_FRAMEBUFFER_UNSUPPORTED";
    case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE: return "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE";
    case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS: return "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS";
    case GL_FRAMEBUFFER_COMPLETE: return "GL_FRAMEBUFFER_COMPLETE";
    default: return "glFramebufferCompleteString: INVALID_ENUM";
  }
}

//Compexity is O(log N + M) where
// N - Number of Extensions already looked at
// M - Number of Extensions looked at in this run (If extension not in alraedy looked at set)
// Note : if you sum up all invocation complexities M's total will never exceed the 
//        number of extensions present
GLboolean glIsExtensionSupported(const std::string &ext)
{
  static std::set<std::string> extensions;
  static GLint numExtensions = 0;
  static GLint extensionsParsed = 0;

  if(!numExtensions)
  {
    //First time this is run
    glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);
  }

  if(extensions.find(ext) != extensions.end())
  {
    //Extension found
    return GL_TRUE;
  }
  else
  {
    //Continue searching through extensions
    for(;numExtensions > extensionsParsed;)
    {
      std::string tmp((const char*)glGetStringi(GL_EXTENSIONS, extensionsParsed++));
      
      //Add to extensions
      extensions.insert(tmp);

      //Check if this is the extensions we are looking for
      if(tmp.compare(ext) == 0)
      {
        //Yes, yes it is
        return GL_TRUE;
      }
    }
  }

  return GL_FALSE;
}

GLvoid APIENTRY glDebugMessageCallbackFunction( GLenum source, GLenum type, GLuint id,
                  GLenum severity, GLsizei length, const GLchar* message, GLvoid* userParam)
{
  gLoge << "Source:   " << glDebugSourceString(source) << std::endl;
  gLoge << "Type:     " << glDebugTypeString(type) << std::endl;
  gLoge << "Severity: " << glDebugSeverityString(severity) << std::endl;
  gLoge << "Message:  " << std::endl << "\t" << message << std::endl;

  //Get Rid of Unused Var Warnings
  id = id;
  userParam = userParam;
  length = length;
}

GLvoid APIENTRY glDebugMessageCallbackFunctionAMD( GLuint id, GLenum category,
                  GLenum severity, GLsizei length, const GLchar* message, GLvoid* userParam)
{
  gLoge << "Category: " << glDebugCategoryAMDString(category) << std::endl;
  gLoge << "Severity: " << glDebugSeverityString(severity) << std::endl;
  gLoge << "Message:  " << std::endl << "\t" << message << std::endl;

  //Get Rid of Unused Var Warnings
  id = id;
  length = length;
  userParam = userParam;
}

GLvoid glVertexAttribPointers( FVertexEnum type )
{
  switch( type )
  {
    case F_VERTEX_3:
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(FVertex3), (GLvoid*) 0);
      glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(FVertex3), (GLvoid*) (sizeof(float) * 3) );
      glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(FVertex3), (GLvoid*) (sizeof(float) * 5) );
      break;
    case F_VERTEX_2:
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(FVertex2), (GLvoid*) 0);
      glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(FVertex2), (GLvoid*) (sizeof(float) * 3) );
      break;
    case F_VERTEX_TEXT:
      glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(FVertexText), (GLvoid*) 0);
      glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(FVertexText), (GLvoid*) (sizeof(float) * 2) );
      glVertexAttribIPointer(2, 1, GL_INT, sizeof(FVertexText), (GLvoid*) (sizeof(float) * 4) );
      break;
    case F_VERTEX_DEFERRED:
      glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(FVertexDeferred), NULL);
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
    case F_VERTEX_TEXT:
      glEnableVertexAttribArray(2);
    case F_VERTEX_2:
      glEnableVertexAttribArray(1);
    case F_VERTEX_DEFERRED:
      glEnableVertexAttribArray(0);
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
    case F_VERTEX_TEXT:
      glDisableVertexAttribArray(2);
    case F_VERTEX_2:
      glDisableVertexAttribArray(1);
    case F_VERTEX_DEFERRED:
      glDisableVertexAttribArray(0);
   default:
      std::cerr << "F_INVALID_ENUM" << std::endl;
  }
}
