/*
 * File :
 *      ./Model/Model.cpp
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      Definitions of ./Model/Model.h
 */

#include "Model.h"

#include "../Graphics/Graphics.h"

#include <glm/glm.hpp>
#include <fstream>
#include <vector>
#include <set>
#include <tuple>
#include <algorithm>
#include <iostream>

FModel::FModel()
{
  vertices = NULL;
  indices = NULL;
  numVertices = numIndices = 0;

  vbo = ibo = 0;

  tTexture = tOverlay = tHeightMap = tNormalMap = 0;
}

FModel::~FModel()
{
  if(vertices)
    delete[] vertices;
  if(indices)
    delete[] indices;

  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &ibo);

  //Don't remove Textures as it is not the model's textures
}

GLint FModel::loadModelFromVertices(FVertex3 *vertices, GLuint numVertices)
{
  //Generate Indices
  GLuint* tmpIndices = new GLuint[numVertices];

  for(GLuint i = 0;i < numVertices; i++)
    tmpIndices[i] = i;

  return loadModelFromVerticesAndIndices(vertices, numVertices, tmpIndices, numVertices);

}

GLint FModel::loadModelFromVerticesAndIndices(FVertex3 *vertices, GLuint numVertices,
                                              GLuint* indices, GLuint numIndices)
{
  //Create Vertex Buffer
  glGenBuffers(1, &this->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof( FVertex3 ) * numVertices, vertices, GL_STATIC_DRAW);

  //Create Index Buffer
  glGenBuffers(1, &this->ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(GLuint), indices, GL_STATIC_DRAW);

  //Set Data
  this->indices = indices;
  this->numIndices = numIndices;
  this->vertices = vertices;
  this->numVertices = numVertices;

  return 0;
}

GLvoid FModel::attachTexture(FTexture *tex, F_MODEL_TEXTURE_ENUM type)
{
  //TODO Use Resource Manager
  switch(type)
  {
    case F_MODEL_TEXTURE_TEXTURE:   this->tTexture = tex;
    case F_MODEL_TEXTURE_NORMAL:    this->tNormalMap = tex;
    case F_MODEL_TEXTURE_HEIGHT:    this->tHeightMap = tex;
    case F_MODEL_TEXTURE_OVERLAY:   this->tOverlay = tex;
  }
}

