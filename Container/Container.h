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

struct FTextVertex
{
  glm::vec2 pos;
  glm::vec2 tex;
  glm::vec3 col;
};

struct FVertex
{
  glm::vec3 pos;
  glm::vec3 col;
  glm::vec2 tex;
  glm::vec3 nor;
};

#endif //_F_H_CONTAINER
