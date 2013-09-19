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
  glm::vec2 pos;
  glm::vec3 col;
  glm::vec2 tex;
};

//3D Vertex
struct FVertex3
{
  glm::vec3 pos;
  glm::vec3 col;
  glm::vec2 tex;
  glm::vec3 nor;
};

#endif //_F_H_CONTAINER
