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
#include "../Container/Container.h"

const GLchar* glErrorString(GLenum err);
#if defined(GL_ARB_debug_output) && GL_ARB_debug_output == 1
const GLchar* glDebugSourceString(GLenum source);
const GLchar* glDebugTypeString(GLenum type);
const GLchar* glDebugSeverityString(GLenum severe);
#endif //DEBUG && GL_ARB_debug_output

#ifndef DEBUG
#define GL_ERROR_ASSERT() { GLenum err = glGetError(); if(err) { std::cerr << "glGetError: " << glErrorString(err) << std::endl; assert(GL_FALSE); } }
#else
#define GL_ERROR_ASSERT() /* No Assert */
#endif //DEBUG

GLvoid glVertexAttribPointers( FVertexEnum type );
GLvoid glEnableVertexAttribs( FVertexEnum type );
GLvoid glDisableVertexAttribs( FVertexEnum type );

#if defined(GL_KHR_debug) && GL_KHR_debug == 1
GLvoid glDebugMessageCallback( GLenum source, GLenum type, GLuint id, GLenum severity,
                               GLsizei lengths, const GLchar* message, GLvoid* userParam)
#endif //DEBUG && GL_ARB_debug_output

#endif //_F_H_FGLEXT_
