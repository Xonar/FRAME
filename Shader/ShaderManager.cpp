/*
 * File :
 *      ./Shader/ShaderManager.cpp
 *
 * Author : 
 *      Xonar <Paul le Roux>
 *
 * Description :
 *      Definitions of ./Shader/ShaderManager.h
 *      
 */
 
#include "ShaderManager.h"
#include "../Lib/Log.h"
#include "../Lib/Files.h"

FShaderManager::FShaderManager()
{
  //Automatic
}

FShader* FShaderManager::loadShader(const std::string name, char const * const vs,
                                    char const * const fs)
{
  //Load Shader
  FShader* s = new FShader();
  if(vs != NULL) s->loadShader(vs, GL_VERTEX_SHADER);
  if(fs != NULL) s->loadShader(fs, GL_FRAGMENT_SHADER);
  s->loadProgram();

  //Register Shader
  this->registerShader(name, s);

  //Return Shader
  return s;
}

FShader* FShaderManager::loadShader(const std::string name, char const * const vs,
                                    char const * const gs, char const * const fs)
{
  //Load Shader
  FShader* s = new FShader();
  if(vs != NULL) s->loadShader(vs, GL_VERTEX_SHADER);
  if(gs != NULL) s->loadShader(gs, GL_GEOMETRY_SHADER);
  if(fs != NULL) s->loadShader(fs, GL_FRAGMENT_SHADER);
  s->loadProgram();

  //Register Shader
  this->registerShader(name, s);

  //Return Shader
  return s;
}

FShader* FShaderManager::loadShader(const std::string name, char const * const vs,
                                    char const * const gs, char const * const tc,
                                    char const * const te, char const * const fs)
{
  //Load Shader
  FShader* s = new FShader();
  if(vs != NULL) s->loadShader(vs, GL_VERTEX_SHADER);
  if(gs != NULL) s->loadShader(gs, GL_FRAGMENT_SHADER);
  if(tc != NULL) s->loadShader(tc, GL_TESS_CONTROL_SHADER);
  if(te != NULL) s->loadShader(te, GL_TESS_EVALUATION_SHADER);
  if(fs != NULL) s->loadShader(fs, GL_FRAGMENT_SHADER);
  s->loadProgram();

  //Register Shader
  this->registerShader(name, s);

  //Return Shader
  return s;
}

GLuint FShaderManager::getShaderObject(const std::string &shaderPath, const GLenum type)
{
  gLogv << "Loading Shader : " << shaderPath;

  //Check if Shader is not already compiled
  auto it = objects.find(shaderPath);

  if(it != objects.end())
  {
    gLogv << " (cached)" << std::endl;
    return it->second;
  }
  else
    gLogv << std::endl;

  //Fetch Shader Source
  std::string shaderSrc = readFileIntoString(shaderPath);
  if(shaderSrc.compare("") == 0)
  {
    gLoge << "Cant compile shader without source!" << std::endl;
    return 0;
  }

  //TODO Modify Source to Insert Defines
  
  //Create and Compile Shader
  GLint result;
  GLuint shader = glCreateShader(type);

  const char* pSrc = &shaderSrc[0];

  glShaderSource(shader, 1, &pSrc, NULL);
  glCompileShader(shader);

  //Check if succeeded
  glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

  if(result == GL_FALSE)
  {
    FShader::printShaderLog(shader);
    return 0;
  }

  //Register Shader Object
  objects[shaderPath] = shader;

  return shader;
}

void FShaderManager::registerShader(std::string name, FShader* shader)
{
  //Check for existing shader with that name
  auto it = shaders.find(name);
  if(it != shaders.end())
    gLogw << "Warning Overwriting reference to shader : " << name << std::endl;

  //Set Shader
  shaders[name] = shader;
}

void FShaderManager::setShaderMacro(std::string name, std::string value)
{
  defines[name] = value;
}

std::string FShaderManager::getShaderMacro(std::string name)
{
  return defines[name];
}
