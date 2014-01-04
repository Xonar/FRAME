/*
 * File :
 *      ./Container/Container.h
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      All Containers used by FRAME
 */

#ifndef _F_H_CONTAINER_
#define _F_H_CONTAINER_

#include <glm/glm.hpp>

#include "../Graphics/Graphics.h"

//Text Vertex
struct FVertexText
{
  glm::vec2 pos;
  glm::vec2 tex;
  int index;
};

#define NUM_BONES_PER_VERTEX 4

//Struct thats used for bone weight
struct FVertexBoneData
{
  GLfloat weight[NUM_BONES_PER_VERTEX];
  GLuint boneID[NUM_BONES_PER_VERTEX];
};

//2D Vertex
struct FVertex2
{
  glm::vec3 pos;
  glm::vec2 tex;
};

//3D Vertex
struct FVertex3
{
  glm::vec3 pos;
  glm::vec2 tex;
  glm::vec3 nor;
};

//Deferred Vertex
struct FVertexDeferred
{
  glm::vec2 pos;
};

enum FVertexEnum { F_VERTEX_TEXT, F_VERTEX_3, F_VERTEX_2, F_VERTEX_DEFERRED };

#endif //_F_H_CONTAINER
