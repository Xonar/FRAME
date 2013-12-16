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

#include <glm/gtx/vector_angle.hpp>

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

FVertex3* FModelPart::getVerticesCopy() const
{
  FVertex3* tmp = new FVertex3[this->vertices.size()];
  std::copy(this->vertices.begin(), this->vertices.end(), tmp);
  return tmp;
}

GLuint* FModelPart::getIndicesCopy() const
{
  GLuint* tmp = new GLuint[this->indices.size()];
  std::copy(this->indices.begin(), this->indices.end(), tmp);
  return tmp;
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
                        glm::vec3(0.f) //Zero Initail Normals
                      };

  //Compute Normals
  for(GLuint i = 0;i < numVertices;i+=3)
  {
    glm::vec3 v0 = vertexBuffer[i+0].pos;
    glm::vec3 v1 = vertexBuffer[i+1].pos;
    glm::vec3 v2 = vertexBuffer[i+2].pos;

    glm::vec3 norm, cross;
    cross = glm::cross(v2 - v0, v1 - v0);
    norm = glm::normalize(cross);

    vertexBuffer[i+0].nor += norm * glm::angle(glm::normalize(v1 - v0), glm::normalize(v2 - v0));
    vertexBuffer[i+1].nor += norm * glm::angle(glm::normalize(v0 - v1), glm::normalize(v2 - v1));
    vertexBuffer[i+2].nor += norm * glm::angle(glm::normalize(v0 - v2), glm::normalize(v1 - v2));
  }

  for(GLuint i =0; i < numVertices;i++)
    vertexBuffer[i].nor = glm::normalize(vertexBuffer[i].nor);

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
