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
#include "../Lib/FGLext.h"

#include <glm/glm.hpp>
#include <fstream>
#include <iostream>

FModel::FModel()
{
  vertices = NULL;
  indices = NULL;
  numVertices = numIndices = 0;

  vbo = ibo = 0;

  tTexture = tHeightMap = tNormalMap = 0;
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

GLint FModel::loadModelFromVertices(FVertex3 * const vertices, const GLuint numVertices)
{
  //Generate Indices
  this->indices  = new GLuint[numVertices];

  for(GLuint i = 0;i < numVertices; i++)
    this->indices[i] = i;

  return loadModelFromVerticesAndIndices(vertices, numVertices, this->indices, numVertices);
}

GLint FModel::loadModelFromVerticesAndIndices(FVertex3 * const vertices, const GLuint numVertices,
                                              GLuint * const indices, const GLuint numIndices)
{
  //Set Data
  this->indices = indices;
  this->numIndices = numIndices;
  this->vertices = vertices;
  this->numVertices = numVertices;

  //Create Vertex Array Object
  glGenVertexArrays(1, &this->vao);
  glBindVertexArray(this->vao);
  glEnableVertexAttribArray(this->vao);

  //Create Vertex Buffer Object
  glGenBuffers(1, &this->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof( FVertex3 ) * this->numVertices, this->vertices, GL_STATIC_DRAW);

  //Enable Vertex Attrib Arrays
  glEnableVertexAttribs( F_VERTEX_3 );
  glVertexAttribPointers( F_VERTEX_3 );

  //Create Index Buffer Object
  glGenBuffers(1, &this->ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->numIndices * sizeof(GLuint), this->indices, GL_STATIC_DRAW);

  return 0;
}

GLvoid FModel::readyDraw()
{
  glBindVertexArray(this->vao);
}

GLvoid FModel::readyTextures()
{
  if(this->tTexture)
  {
    this->tTexture->bindTexture(GL_TEXTURE0);
  }

  if(this->tHeightMap)
  {
    tHeightMap->bindTexture(GL_TEXTURE1);
  }

  if(this->tNormalMap)
  {
    tNormalMap->bindTexture(GL_TEXTURE2);
  }
}

GLvoid FModel::draw()
{
  glDrawElements(GL_TRIANGLES, this->numIndices, GL_UNSIGNED_INT, NULL);
  //glDrawArrays(GL_TRIANGLES, 0, 12*3);
}

GLint FModel::loadModelFromVertexAndTextureArray(const GLfloat *const vertices, 
      const GLfloat *const uvs, const GLuint numVertices)
{
  this->vertices = new FVertex3[numVertices];

  for(GLuint i = 0; i<numVertices;i++)
  {
    this->vertices[i] = {glm::vec3(vertices[3*i+0],vertices[3*i+1], vertices[3*i+2]), 
                   glm::vec2(uvs[i*2+0], uvs[i*2+1]),
                   glm::vec3(0.f)};
  }

  //Compute Normals (Only works for non-shared vertices at the moment)
  for(GLuint i = 0;i < numVertices;i+=3)
  {
    glm::vec3 v0 = this->vertices[i+0].pos;
    glm::vec3 v1 = this->vertices[i+1].pos;
    glm::vec3 v2 = this->vertices[i+2].pos;

    glm::vec3 norm, cross;
    cross = glm::cross(v2 - v0, v1 - v0);
    norm = glm::normalize(cross);

    this->vertices[i+0].nor = norm;
    this->vertices[i+1].nor = norm;
    this->vertices[i+2].nor= norm;
  }

  return loadModelFromVertices(this->vertices, numVertices);
}

GLvoid FModel::attachTexture(FTexture2D * const tex, const F_MODEL_TEXTURE_ENUM type)
{
  //TODO Use Resource Manager
  switch(type)
  {
    case F_MODEL_TEXTURE_TEXTURE:   this->tTexture = tex;
    case F_MODEL_TEXTURE_NORMAL:    this->tNormalMap = tex;
    case F_MODEL_TEXTURE_HEIGHT:    this->tHeightMap = tex;
  }
}

