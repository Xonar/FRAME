/*
 * File :
 *      ./Shader/Shader.cpp
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      Definitions of ./Shader/Shader.h
 */

#include "Shader.h"

#include "../Graphics/Graphics.h"
#include "../Lib/Files.h"

#include <iostream>

FShader::FShader()
{
  this->glProg = 0;
  this->vs = this->gs = this->tc = this->te = this->fs = 0;
}

FShader::~FShader()
{
  freeProgram();
}

void FShader::freeProgram()
{
  if(glProg)
    glDeleteProgram(this->glProg);
}

GLint FShader::bind()
{
  glUseProgram(this->glProg);

  if(glGetError() != GL_NO_ERROR)
  {
    printProgramLog(this->glProg);
    return 1;
  }

  return 0;
}

void FShader::unbind()
{
  glUseProgram(0);
}

void FShader::printProgramLog(GLuint program)
{
  if(program && glIsProgram(program))
  {
    int len = 0;
    int actLen = 0;
    
    glGetProgramiv( program, GL_INFO_LOG_LENGTH, &len);
    
    char* log = new char[len];

    glGetProgramInfoLog( program, len, &actLen , log);

    if(actLen > 0)
      std::cerr << log << std::endl;

    delete[] log;
  }
  else
  {
    std::cerr << "Invalid Program : " << program << std::endl;
  }
}

void FShader::printShaderLog(GLuint shader)
{
  if(shader && glIsShader(shader))
  {
    int len = 0;
    int actLen = 0;
    
    glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &len);
    
    char* log = new char[len];

    glGetShaderInfoLog( shader, len, &actLen , log);

    if(actLen > 0)
      std::cerr << log << std::endl;

    delete[] log; 
  }
  else
  {
    std::cerr << "Invalid Shader : " << shader << std::endl;
  }
}

GLint FShader::loadShader(std::string shader, GLenum type)
{
  GLuint* pShader;

  switch(type)
  {
    case GL_VERTEX_SHADER:
      if(vs)
      {
        std::cerr << "Vertex Shader Already Exists!" << std::endl;
        return 1;
      }
      pShader = &vs;
      break;
    case GL_GEOMETRY_SHADER:
      if(gs)
      {
        std::cerr << "Geometry Shader Already Exists!" << std::endl;
        return 1;
      }
      pShader = &gs;
      break;
    case GL_TESS_EVALUATION_SHADER:
      if(te)
      {
        std::cerr << "Tesselation Evaluation Shader Already Exists!" << std::endl;
        return 1;
      }
      pShader = &te;
      break;
    case GL_TESS_CONTROL_SHADER:
      if(tc)
      {
        std::cerr << "Tesselation Control Shader Already Exists!" << std::endl;
        return 1;
      }
      pShader = &tc;
      break;
    case GL_FRAGMENT_SHADER:
      if(fs)
      {
        std::cerr << "Fragment Shader Already Exists!" << std::endl;
        return 1;
      }
      pShader = &fs;
      break;
  }

  std::string shaderSrc = readFileIntoString(shader);
  if(shaderSrc.compare(""))
  {
    std::cerr << "Cant compile shader withour source!" << std::endl;
    return 1;
  }

  GLint result;

  GLuint shader = glCreateShader(type);

  const char* pSrc = &shaderSrc[0];

  glShaderSource(shader, 1, &pSrc, NULL);
  glCompileShader(shader);

  glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

  if(result == GL_FALSE)
  {
    printShaderLog(shader);
    return 1;
  }

  return 0;
}
