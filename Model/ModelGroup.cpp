/*
 * File :
 *      ./Model/ModelGroup.cpp
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      Definitions of ./Model/ModelGroup.h
 */

#include "ModelGroup.h"
#include "../Lib/FGLext.h"
#include "../Lib/Log.h"


#include <algorithm>

FModelGroup::FModelGroup()
{

}

void FModelGroup::readyModelGroup() const
{
  glBindVertexArray(this->vao);
}

void FModelGroup::drawModelGroup() const
{
  for(const FModel *it : this->models)
  {
    it->drawModel();
  }
}

GLvoid FModelGroup::addModel(FModel *model)
{
  this->models.push_back(model);
}

GLvoid FModelGroup::addModels(FModel **models, const GLuint modelNum)
{
  this->models.insert(this->models.end(), models, models + modelNum);
}

GLvoid FModelGroup::addMaterial(FMaterial *material)
{
  this->materials.push_back(material);
}

GLvoid FModelGroup::addMaterials(FMaterial **materials, const GLuint materialNum)
{
  this->materials.insert(this->materials.end(), materials, materials + materialNum);
}

GLvoid FModelGroup::finalize()
{
  //Create OpenGL buffers
  glGenVertexArrays(1, &this->vao);
  glGenBuffers(1, &this->vbo);
  glGenBuffers(1, &this->ibo);

  //Bind Buffers
  glBindVertexArray(this->vao);
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);

  //Setup VAO
  glVertexAttribPointers(F_VERTEX_3);
  glEnableVertexAttribs(F_VERTEX_3);

  //Get Total Size of Indices and Vertices and set up models
  GLuint indicesStart = 0;
  GLuint baseVertex = 0;
  
  for(FModel* modelIt : models)
  {
    for(FModelPart* part : modelIt->getParts())
    {
      const std::vector<GLuint>& indices = part->getIndices();
      const std::vector<FVertex3>& vertices = part->getVertices();
      part->setupPart(baseVertex, indicesStart);
      indicesStart += indices.size();
      baseVertex += vertices.size();
    }
  }

  GLsizei verticesSize = sizeof(FVertex3) * baseVertex;
  GLsizei indicesSize = sizeof(GLuint) * indicesStart;

  //Allocate Buffers
  glBufferData(GL_ARRAY_BUFFER, verticesSize, NULL, GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, NULL, GL_STATIC_DRAW);

  GLuint indicesSizeCounter = 0;
  GLuint verticesSizeCounter = 0;

  //Map Buffers
  FVertex3* verticesMap = (FVertex3*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
  GLuint* indicesMap = (GLuint*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);

  //Push Data to the GPU
  for(FModel* modelIt : models)
  {
    for(FModelPart* part : modelIt->getParts())
    {
      const std::vector<GLuint>& indices = part->getIndices();
      const std::vector<FVertex3>& vertices = part->getVertices();
      std::copy(indices.begin(), indices.end(), indicesMap + indicesSizeCounter);
      std::copy(vertices.begin(), vertices.end(), verticesMap + verticesSizeCounter);
      indicesSizeCounter += indices.size();
      verticesSizeCounter += vertices.size();
    }
  }

  //Unmap Buffers
  glUnmapBuffer(GL_ARRAY_BUFFER);
  glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
  indicesMap = NULL;
  verticesMap = NULL;
}
