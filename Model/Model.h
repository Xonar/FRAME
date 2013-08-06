/*
 * File :
 *      ./Model/Model.h
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      The FModel class is a handler for Model Objects
 */

#ifndef _F_H_MODEL_
#define _F_H_MODEL_

#include "../Container/Container.h"
#include "../Texture/Texture.h"

#include <SDL2/SDL_opengl.h>
#include <string>

class FModel
{
  private:
  
  //Model Data:
  FVertex *vertices;
  GLuint numVertices;

  GLuint *indices;
  GLuint numIndices;

  //Buffer Objects
  GLuint vbo;
  GLuint ibo;

  //Texture Objects
  FTexture *tTexture;
  FTexture *tOverlay;
  FTexture *tHeightMap;
  FTexture *tNormalMap;
  
  public:
  FModel();
  ~FModel();

  GLint draw();

  GLint loadModelFormFileObj(std::string path);
  GLint loadModelFromVertices(FVertex vertices);
};

#endif //_F_H_MODEL_
