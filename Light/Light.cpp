/*
 * File :
 *      ./Light/Light.cpp
 *
 * Author : 
 *      Xonar <Paul le Roux>
 *
 * Description :
 *      Definitions of ./Light/Light.h
 *      
 */
 
#include "Light.h"

FLight::FLight(glm::vec3 diffuse)
{
  this->diffuse = diffuse;
}

const glm::vec3& FLight::getDiffuse() const
{
  return this->diffuse;
}

FLightDirectional::FLightDirectional(glm::vec3 diffuse, glm::vec3 direction) :
  FLight(diffuse)
{
  this->direction = glm::normalize(direction);
}

const glm::vec3& FLightDirectional::getDirection() const
{
  return this->direction;
}

FLightPoint::FLightPoint(glm::vec3 diffuse, GLfloat distance) :
  FLight(diffuse)
{
  this->distance = distance;
}
