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
  GLuint* tmpIndices = new GLuint[vertices];

  for(int i = 0;i < numVertices; i++)
    tmpIndices[i] = i;

  return loadModelFromVerticesAndIndices(vertices, numVertices, tmpIndices, numVertices);

}


GLint loadModelFromVerticesAndIndices(FVertex3 *vertices, GLuint numVertices, GLuint* indices, GLuint numIndices)
{
  //Create Vertex Buffer
  glGenBuffers(1, &this->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, sizeof( FVertex ) * numVertices, vertices, GL_STATIC_DRAW);

  //Create Index Buffer
  glGenBuffers(1, %this->ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(GLuint), indices, GL_STATIC_DRAW);

  //Set Data
  this->indices = indices;
  this->numIndices = numIndices;
  this->vertices = vertices;
  this->numVertices = numVertices;

  return 0;
}
