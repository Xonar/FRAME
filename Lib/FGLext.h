/*
 * File :
 *      ./Lib/FGLext.h
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      FRAME OpenGL extension and extra functionality
 */

#ifndef _F_H_FGLEXT_
#define _F_H_FGLEXT_

#include <SDL2/SDL_opengl.h>
#include <string>

#include "../Container/Container.h"

const GLchar* glErrorString(GLenum err);
const GLchar* glDebugSourceString(GLenum source);
const GLchar* glDebugTypeString(GLenum type);
const GLchar* glDebugSeverityString(GLenum severe);

GLboolean glIsExtensionSupported(const std::string ext);

#ifndef DEBUG
#define GL_ERROR_ASSERT() { GLenum err = glGetError(); if(err) { std::cerr << "glGetError: " << glErrorString(err) << std::endl; assert(GL_FALSE); } }
#else
#define GL_ERROR_ASSERT() /* No Assert */
#endif //DEBUG

GLvoid glVertexAttribPointers( FVertexEnum type );
GLvoid glEnableVertexAttribs( FVertexEnum type );
GLvoid glDisableVertexAttribs( FVertexEnum type );

GLvoid glDebugMessageCallbackFunction( GLenum source, GLenum type, GLuint id, GLenum severity,
                               GLsizei lengths, const GLchar* message, GLvoid* userParam);

#endif //_F_H_FGLEXT_
