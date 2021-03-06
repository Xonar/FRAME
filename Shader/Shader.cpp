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
#include "../Lib/Log.h"
#include "ShaderManager.h"


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

GLint FShader::bind() const
{
  glUseProgram(this->glProg);

  if(glGetError() != GL_NO_ERROR)
  {
    printProgramLog(this->glProg);
    return 1;
  }

  return 0;
}

void FShader::unbind() const
{
  glUseProgram(0);
}

void FShader::printProgramLog(const GLuint program)
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
    gLogw << "Invalid Program : " << program << std::endl;
  }
}

void FShader::printShaderLog(const GLuint shader)
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
    gLoge << "Invalid Shader : " << shader << std::endl;
  }
}

GLuint FShader::getShader(const GLenum type)
{
  switch(type)
  {
    case GL_VERTEX_SHADER:
      return vs;
    case GL_GEOMETRY_SHADER:
      return gs;
    case GL_TESS_EVALUATION_SHADER:
      return te;
    case GL_TESS_CONTROL_SHADER:
      return tc;
    case GL_FRAGMENT_SHADER:
      return fs;
    default:
      gLoge << "Invalid GLenum passed to getShader : " << type << std::endl;
      return 0;
  }
}

GLint FShader::loadShader(const std::string &shader, const GLenum type)
{
  GLuint* pShader = NULL;

  //Check that the shader isn't overwritten
  switch(type)
  {
    case GL_VERTEX_SHADER:
      if(vs)
      {
        gLogw << "Vertex Shader Already Exists!" << std::endl;
        return 1;
      }
      pShader = &vs;
      break;
    case GL_GEOMETRY_SHADER:
      if(gs)
      {
        gLogw << "Geometry Shader Already Exists!" << std::endl;
        return 1;
      }
      pShader = &gs;
      break;
    case GL_TESS_EVALUATION_SHADER:
      if(te)
      {
        gLogw << "Tesselation Evaluation Shader Already Exists!" << std::endl;
        return 1;
      }
      pShader = &te;
      break;
    case GL_TESS_CONTROL_SHADER:
      if(tc)
      {
        gLogw << "Tesselation Control Shader Already Exists!" << std::endl;
        return 1;
      }
      pShader = &tc;
      break;
    case GL_FRAGMENT_SHADER:
      if(fs)
      {
        gLogw << "Fragment Shader Already Exists!" << std::endl;
        return 1;
      }
      pShader = &fs;
      break;
  }

  //Fetch Shader Source
  *pShader = gShaderManager->getShaderObject(shader, type);

  return 0;
}

GLint FShader::loadProgram()
{
  //Create Program
  this->glProg = glCreateProgram();

  if(!glProg)
  {
    gLoge << "Failed Creating a Shader Program Object!" << std::endl;

    gLoge << "GL Error: " << glGetError() << std::endl;

    return 1;
  }

  //Attach all shaders
  if(this->vs)
    glAttachShader(this->glProg, this->vs);
  if(this->gs)
    glAttachShader(this->glProg, this->gs);
  if(this->tc)
    glAttachShader(this->glProg, this->tc);
  if(this->te)
    glAttachShader(this->glProg, this->te);
  if(this->fs)
    glAttachShader(this->glProg, this->fs);

  //Link Shaders
  glLinkProgram(this->glProg);

  //Check if it linked succesfully
  {
    GLint linkStatus = GL_FALSE;
    glGetProgramiv (this->glProg, GL_LINK_STATUS, &linkStatus);
    if(linkStatus != GL_TRUE)
    {
      gLoge << "Failed linking program : " << std::endl;
      this->printProgramLog(this->glProg);
    }
  }

  return 0;
}
