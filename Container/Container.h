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

//Text Vertex
struct FTextVertex
{
  glm::vec2 pos;
  glm::vec2 tex;
  glm::vec3 col;
};

//2D Vertex
struct FVertex2
{
  glm::vec3 pos;
  glm::vec2 tex;
  glm::vec3 col;
};

//3D Vertex
struct FVertex3
{
  glm::vec3 pos;
  glm::vec3 col;
  glm::vec2 tex;
  glm::vec3 nor;
};

enum FVertexEnum { F_VERTEX_TEXT, F_VERTEX_3, F_VERTEX_2 };

#endif //_F_H_CONTAINER
