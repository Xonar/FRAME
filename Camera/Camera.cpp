/*
 * File :
 *      ./Camera/Camera.h
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      Definitions of ./Camera/Camera.h
 */

#include "Camera.h"
#include "../Graphics/Graphics.h"
#include "../Lib/Log.h"

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>


FCamera::FCamera()
{
  this->x = this->y = this->width = this->height = 0;

  this->updateWorldViewMatrix = true;
  this->updateViewScreenMatrix = true;
  this->ready = false;

  this->pos = glm::vec3(0,0,0);
  this->dir = glm::vec3(0,0,1);
  this->up  = glm::vec3(0,1,0);

  this->ubo = 0;

  this->WorldViewMatrix = this->ViewScreenMatrix = glm::mat4();
}

FCamera::~FCamera()
{
  if(this->ubo)
    glDeleteBuffers(1, &this->ubo);

  this->ubo = 0;
}

GLint FCamera::update()
{
  //If intialized
  if(this->ready)
  {
    //Only Update if it's neccesary
    if(this->updateWorldViewMatrix)
    {
      this->WorldViewMatrix = glm::lookAt(pos, pos+dir, up);
    }

    //If Something Changed
    if(this->updateViewScreenMatrix || this->updateWorldViewMatrix)
    {
      this->wvs = this->ViewScreenMatrix * this->WorldViewMatrix;
      this->svw = glm::inverse(wvs);
      this->updateViewScreenMatrix = this->updateWorldViewMatrix = false;
    }
  }
  else
  {
    gLogw << "Trying to use Camera before it's ready!" << std::endl;
    return 1;
  }

  return 0;
}

GLvoid FCamera::setViewPort(const GLint x, const GLint y, const GLint w, const GLint h)
{
  this->x = x;
  this->y = y;
  this->width = w;
  this->height = h;
  this->aspect = (float)w/h;
}

//Init 3D Ortho Matrix
GLint FCamera::InitOrthoMatrix( const float left, const float right, const float bottom,
                                const float top, const float zNear, const float zFar)
{
  this->x = left;
  this->width = right - left;
  this->y = bottom;
  this->height = top - bottom;
  this->aspect = (float)this->width/this->height;

  this->updateViewScreenMatrix = true;

  this->ViewScreenMatrix = glm::ortho(left,right,bottom,top,zNear,zFar);

  this->ready = true;
  return 0;
}

//Init 2D Ortho Matrix
GLint FCamera::InitOrthoMatrix(const float left, const float right, const float bottom,
                               const float top)
{
  this->x = left;
  this->width = right - left;
  this->y = bottom;
  this->height = top - bottom;
  this->aspect = (float)this->width/this->height;

  this->updateViewScreenMatrix = true;
  this->updateWorldViewMatrix = false;

  this->ViewScreenMatrix = glm::ortho(left,right,bottom,top);

  this->ready = true;
  return 0;
}

//Init Projection Matrix
GLint FCamera::InitProjectionMatrix(const float fovy, const float zNear, const float zFar)
{
  this->updateViewScreenMatrix = true;
  this->ViewScreenMatrix = glm::perspective(fovy, this->aspect, zNear, zFar);

  this->ready = true;
  return 0;
}

GLvoid FCamera::setPosition(const glm::vec3 &pos)
{
  this->pos = pos;
  this->updateWorldViewMatrix = true;
}

GLvoid FCamera::lookAt(const glm::vec3 &lookAt)
{
  this->dir = lookAt - pos;
  this->updateWorldViewMatrix = true;
}

GLvoid FCamera::setDirection(const glm::vec3 &dir)
{
  this->dir = dir;
  this->updateWorldViewMatrix = true;
}

GLvoid FCamera::setUp(const glm::vec3 &up)
{
  this->up = up;
  this->updateWorldViewMatrix = true;
}

GLvoid FCamera::use()
{
  glViewport(this->x,this->y,this->width,this->height);
  this->update();
}

//Use Camera (No UBO)
void FCamera::setMatrixUniform(const GLuint uniform) const
{
  glUniformMatrix4fv(uniform, 1, GL_FALSE, &wvs[0][0] );
}

void FCamera::setInverseMatrixUniform(const GLuint uniform) const
{
  glUniformMatrix4fv(uniform, 1, GL_FALSE, &svw[0][0] );
}
