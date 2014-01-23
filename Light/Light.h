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
  public:
    FLight(glm::vec3 diffuse);
    const glm::vec3& getDiffuse() const;
};

class FLightDirectional : public FLight
{
  protected:
    glm::vec3 direction;
  public:
    FLightDirectional(glm::vec3 diffuse, glm::vec3 direction);
    const glm::vec3& getDirection() const;
};

class FLightPoint : public FLight
{
  protected:
    glm::vec3 position;
    GLfloat distance;
  public:
    FLightPoint(glm::vec3 diffuse, float distance);
    GLfloat getDistance() const;
};

#endif // _F_H_LIGHT_
