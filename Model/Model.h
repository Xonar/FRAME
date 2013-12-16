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
#include "../Graphics/Graphics.h"

#include "ModelPart.h"

#include <string>

enum F_MODEL_TEXTURE_ENUM { F_MODEL_TEXTURE_TEXTURE, 
  F_MODEL_TEXTURE_HEIGHT, F_MODEL_TEXTURE_NORMAL };

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
  GLuint vao;

  //Texture Objects
  FTexture2D *tTexture;
  FTexture2D *tHeightMap;
  FTexture2D *tNormalMap;
  
  public:
  FModel();
  ~FModel();

  GLvoid readyDraw() const;
  GLvoid readyTextures() const;
  GLvoid draw() const;

  GLint loadModelFormFileObj(const std::string &path);
  GLint loadModelFromVertices(FVertex3 * const vertices, const GLuint numVertices);
  GLint loadModelFromVerticesAndIndices(FVertex3 *const vertices, const GLuint numVertices, 
                                        GLuint* const indices, const GLuint numIndices);
  GLint loadModelFromVertexAndTextureArray(const GLfloat * const vertices, const GLfloat * const uvs, const GLuint numVertices);
  GLint loadModelFromPart(const FModelPart* part);

  GLvoid attachTexture(FTexture2D *const tex, const F_MODEL_TEXTURE_ENUM type);
};

#endif //_F_H_MODEL_
