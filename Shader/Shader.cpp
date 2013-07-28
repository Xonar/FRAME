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
  glUseProgram(NULL);
}

void FShader::printProgramLog(GLuint program)
{
  if(program && glIsProgram(program))
  {
    int len = 0;
    int actLen = 0;
    
    glGetProgamiv( program, GL_INFO_LOG_LENGTH, &len);
    
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
