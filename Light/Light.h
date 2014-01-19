/*
 * File :
 *      ./Light/Light.h
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      Classes that handle lights
 */

#ifndef _F_H_LIGHT_
#define _F_H_LIGHT_

#include <glm/glm.hpp>
#include "../Graphics/Graphics.h"

class FLight
{
  protected:
    glm::vec3 diffuse;
};

class FLightDirectional : public FLight
{
  protected:
    glm::vec3 direction;
};

class FLightPoint : public FLight
{
  protected:
    glm::vec3 position;
    GLfloat distance;
};

#endif // _F_H_LIGHT_
