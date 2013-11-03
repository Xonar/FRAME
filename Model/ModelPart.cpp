/*
 * File :
 *      ./Model/Model.cpp
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      Definitions of ./Model/ModelPart.h
 */

#include "ModelPart.h"

FModelPart::FModelPart()
{
  this->baseVertex = this->indicesCount = this->indicesStart = 0;
}

FModelPart::~FModelPart()
{
  this->releaseVertices();
  this->releaseIndices();
}

const std::vector<FVertex3>& FModelPart::getVertices() const
{
  return this->vertices;
}
const std::vector<GLuint>& FModelPart::getIndices() const
{
  return this->indices;
}

GLvoid FModelPart::releaseVertices()
{
  vertices.clear();
}

GLvoid FModelPart::releaseIndices()
{
  indices.clear();
}

GLint FModelPart::loadModelPartFromVertices(FVertex3* const vertices,const GLuint numVertices)
{
  GLuint* indicesBuffer = new GLuint[numVertices];

  for(GLuint i = 0;i < numVertices;i++)
    indicesBuffer[i] = i;

  GLint ret = this->loadModelPartFromVerticesAndIndices(vertices, numVertices, 
                                                         indicesBuffer, numVertices);

  delete[] indicesBuffer;

  return ret;
}

GLint FModelPart::loadModelPartFromVerticesAndIndices(FVertex3 *const vertices,
                                              const GLuint numVertices, GLuint* const indices,
                                              const GLuint numIndices)
{
  this->vertices = std::vector<FVertex3>(vertices, vertices + numVertices);
  this->indices = std::vector<GLuint>(indices, indices + numIndices);

  return 0;
}

GLint FModelPart::loadModelPartFromVertexAndTextureArray(const GLfloat* const vertices,
                                                const GLfloat* const uvs, const GLuint numVertices)
{
  FVertex3* vertexBuffer = new FVertex3[numVertices];

  for(GLuint i = 0;i < numVertices;i++)
    vertexBuffer[i] = { 
                        glm::vec3(vertices[i*3], vertices[i*3 + 1], vertices[i*3 + 2]), //Pos
                        glm::vec2(uvs[i*2], uvs[i*2 + 1]), //Tex
                        glm::vec3() //Compute Norm Later
                      };

  //Compute Normal
  //TODO

  GLint ret = this->loadModelPartFromVertices(vertexBuffer, numVertices);

  delete[] vertexBuffer;

  return ret;
}

GLint FModelPart::loadModelPartFromVertexTextureAndNormalArray(const GLfloat* const vertices,
                                                const GLfloat* const uvs, const GLfloat* const norm,
                                                const GLuint numVertices)
{
  FVertex3* vertexBuffer = new FVertex3[numVertices];

  for(GLuint i = 0;i < numVertices;i++)
    vertexBuffer[i] = { 
                        glm::vec3(vertices[i*3], vertices[i*3 + 1], vertices[i*3 + 2]), //Pos
                        glm::vec2(uvs[i*2], uvs[i*2 + 1]), //Tex
                        glm::vec3(norm[i*3], norm[i*3+1], norm[i*3+2]) //Norm
                      };

  GLint ret = this->loadModelPartFromVertices(vertexBuffer, numVertices);

  delete[] vertexBuffer;

  return ret;
}
