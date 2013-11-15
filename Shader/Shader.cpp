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
#include "../Global.h"
#include "../Lib/Log.h"


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

void FShader::printProgramLog(const GLuint program) const
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

void FShader::printShaderLog(const GLuint shader) const
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

GLint FShader::loadShader(const std::string &shader, const GLenum type)
{
  gLogv << "Loading Shader : " << shader << std::endl;
  GLuint* pShader = NULL;

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

  std::string shaderSrc = readFileIntoString(shader);
  if(shaderSrc.compare("") == 0)
  {
    gLoge << "Cant compile shader without source!" << std::endl;
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

  if(pShader)
    *pShader = shader;

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
  {
    glAttachShader(this->glProg, this->vs);
    glDeleteShader(this->vs);
    this->vs = 0;
  }
  
  if(this->gs)
  {
    glAttachShader(this->glProg, this->gs);
    glDeleteShader(this->gs);
    this->gs = 0;
  }
  
  if(this->tc)
  {
    glAttachShader(this->glProg, this->tc);
    glDeleteShader(this->tc);
    this->tc = 0;
  }
  
  if(this->te)
  {
    glAttachShader(this->glProg, this->te);
    glDeleteShader(this->te);
    this->te = 0;
  }

  if(this->fs)
  {
    glAttachShader(this->glProg, this->fs);
    glDeleteShader(this->fs);
    this->fs = 0;
  }

  //If OpenGL version < 33 then bind Attribute Location
  glBindAttribLocation(this->glProg, 0, "pos");
  glBindAttribLocation(this->glProg, 1, "tex");
  glBindAttribLocation(this->glProg, 2, "norm");

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
