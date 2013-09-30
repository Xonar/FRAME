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

enum F_MODEL_TEXTURE_ENUM { F_MODEL_TEXTURE_TEXTURE, 
  F_MODEL_TEXTURE_OVERLAY, F_MODEL_TEXTURE_HEIGHT, F_MODEL_TEXTURE_NORMAL };

class FModel
{
  private:
  
  //Model Data:
  FVertex3 *vertices;
  GLuint numVertices;

  GLuint *indices;
  GLuint numIndices;

  //Buffer Objects
  GLuint vbo;
  GLuint ibo;

  //Texture Objects
  FTexture *tTexture;
  FTexture *tHeightMap;
  FTexture *tNormalMap;
  
  public:
  FModel();
  ~FModel();

  GLint readyDraw();
  GLint draw();

  GLint loadModelFormFileObj(std::string path);
  GLint loadModelFromVertices(FVertex3 *vertices, GLuint numVertices);
  GLint loadModelFromVerticesAndIndices(FVertex3 *vertices, GLuint numVertices, 
                                        GLuint* indices, GLuint numIndices);

  GLvoid attachTexture(FTexture *tex, F_MODEL_TEXTURE_ENUM type);
};

#endif //_F_H_MODEL_
