/*
 * File :
 *      ./Shader/ShaderManager.h
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      Manages Loading of Shaders and Shader Programs
 */

#ifndef _F_H_SHADERMANAGER_
#define _F_H_SHADERMANAGER_

//Includes
#include <map>
#include <string>
#include "Shader.h"

//Class
class FShaderManager
{
  //Shader Maps
  //Should not be used in game loop, just during initialization
  std::map<std::string, GLint> objects;
  std::map<std::string, FShader*> shaders;

  //Defines that are sent used by shader compiler
  std::map<std::string, std::string> defines;
public:
  //Constructor Desctructor
  FShaderManager();
  ~FShaderManager();
  
  //Load Shader
  FShader* loadShader(const std::string name, char const * const vs, char const * const fs);
  FShader* loadShader(const std::string name, char const * const vs, char const * const gs,
                      char const * const fs);
  FShader* loadShader(const std::string name, char const * const vs, char const * const gs,
                      char const * const tc, char const * const te, char const * const fs);

  //Load Shader Object
  GLuint getShaderObject(const std::string &filename, const GLenum type);

  //Set Self Loaded FShader
  void registerShader(std::string name, FShader* shader);

  //Get Set Methods
  void setShaderMacro(std::string name, std::string value);
  std::string getShaderMacro(std::string name);
};

//Global Shader Manager
extern FShaderManager* gShaderManager;

#endif // _F_H_SHADERMANAGER_
