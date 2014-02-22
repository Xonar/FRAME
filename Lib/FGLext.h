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

#include <string>

#include "../Container/Container.h"
#include "../Graphics/Graphics.h"

const GLchar* glErrorString(const GLenum err);
const GLchar* glDebugSourceString(const GLenum source);
const GLchar* glDebugTypeString(const GLenum type);
const GLchar* glDebugSeverityString(const GLenum severe);
const GLchar* glDebugCategoryAMDString(const GLenum category);
const GLchar* glFramebufferCompleteString(const GLenum complete);

GLboolean glIsExtensionSupported(const std::string &ext);

#ifndef DEBUG
#define GL_ERROR_ASSERT() { GLenum err = glGetError(); if(err) { std::cerr << "glGetError: " << glErrorString(err) << std::endl; assert(GL_FALSE); } }
#else
#define GL_ERROR_ASSERT() /* No Assert */
#endif //DEBUG

GLvoid glVertexAttribPointers( FVertexEnum type );
GLvoid glEnableVertexAttribs( FVertexEnum type );
GLvoid glDisableVertexAttribs( FVertexEnum type );

GLvoid APIENTRY glDebugMessageCallbackFunction( GLenum source, GLenum type, GLuint id,
                  GLenum severity, GLsizei lengths, const GLchar* message, GLvoid* userParam);
GLvoid APIENTRY glDebugMessageCallbackFunctionAMD( GLuint id, GLenum category,
                  GLenum severity, GLsizei length, const GLchar* message, GLvoid* userParam);

#endif //_F_H_FGLEXT_
