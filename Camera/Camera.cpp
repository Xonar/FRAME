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
#include "../Global.h"
#include "../Lib/Log.h"

#include <glm/gtc/matrix_transform.hpp>


FCamera::FCamera()
{
  this->x = this->y = this->width = this->height = 0;

  this->updateWorldViewMatrix = true;
  this->updateViewScreenMatrix = true;
  this->ready = false;

  this->pos = glm::vec3(0,0,0);
  this->dir = glm::vec3(0,0,1);

  this->ubViewScreen = this->ubWorldView = 0;
}

FCamera::~FCamera()
{
  if(this->ubViewScreen)
    glDeleteBuffers(1, &this->ubViewScreen);
  if(this->ubWorldView)
    glDeleteBuffers(1, &this->ubWorldView);

  this->ubViewScreen = this->ubWorldView = 0;
}

GLint FCamera::updateUBO()
{
  //If intialized
  if(this->ready)
  {
    //Only Update if it's neccesary
    if(this->updateWorldViewMatrix)
    {
      this->WorldViewMatrix = glm::lookAt(pos,pos+dir,glm::vec3(0,1,0));
      this->updateWorldViewMatrix = false;
      
      glBindBuffer(GL_UNIFORM_BUFFER, this->ubWorldView);

      glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), &this->WorldViewMatrix[0][0], GL_DYNAMIC_DRAW);
    }

    //Only update if it's neccesary
    if(this->updateViewScreenMatrix)
    {
      this->updateViewScreenMatrix = false;

      glBindBuffer(GL_UNIFORM_BUFFER, this->ubViewScreen);

      glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), &this->ViewScreenMatrix[0][0], GL_DYNAMIC_DRAW);
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

  //Create a allocate ViewScreen and WorlView Matrix
  glGenBuffers(1, &this->ubViewScreen);
  glBindBuffer(GL_UNIFORM_BUFFER, this->ubViewScreen);
  glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), NULL, GL_STREAM_DRAW);

  glGenBuffers(1, &this->ubWorldView);
  glBindBuffer(GL_UNIFORM_BUFFER, this->ubWorldView);
  glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), NULL, GL_STREAM_DRAW);

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

  //Create a allocate View Screen Matrix
  glGenBuffers(1, &this->ubViewScreen);
  glBindBuffer(GL_UNIFORM_BUFFER, this->ubViewScreen);
  glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), NULL, GL_STREAM_DRAW);

  this->updateViewScreenMatrix = true;
  this->updateWorldViewMatrix = false;

  this->ViewScreenMatrix = glm::ortho(left,right,bottom,top);

  this->ready = true;
  return 0;
}

//Init Projection Matrix
GLint FCamera::InitProjectionMatrix(const float fovy, const float zNear, const float zFar)
{
  //Create a allocate ViewScreen and WorlView Matrix
  glGenBuffers(1, &this->ubViewScreen);
  glBindBuffer(GL_UNIFORM_BUFFER, this->ubViewScreen);
  glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), NULL, GL_STREAM_DRAW);

  glGenBuffers(1, &this->ubWorldView);
  glBindBuffer(GL_UNIFORM_BUFFER, this->ubWorldView);
  glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), NULL, GL_STREAM_DRAW);

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

GLvoid FCamera::use()
{
  glViewport(this->x,this->y,this->width,this->height);
  
  this->updateUBO();
}

void FCamera::bindMatrixWorldViewToUBO(const GLuint block) const
{
  glBindBufferBase(GL_UNIFORM_BUFFER, block, this->ubViewScreen);
}

void FCamera::bindMatrixViewScreenToUBO(const GLuint block) const
{
  glBindBufferBase(GL_UNIFORM_BUFFER, block, this->ubViewScreen);
}

//Use Camera (No UBO)
void FCamera::setMatrixUniform(const GLuint worldView, const GLuint viewScreen) const
{
  glUniformMatrix4fv(worldView, 1, GL_FALSE, &this->WorldViewMatrix[0][0] );
  glUniformMatrix4fv(viewScreen, 1, GL_FALSE, &this->ViewScreenMatrix[0][0] );
}

void FCamera::setMatrixUniformWorldView(const GLuint uniform) const
{
  glUniformMatrix4fv(uniform, 1, GL_FALSE, &this->WorldViewMatrix[0][0] );
}

void FCamera::setMatrixUniformViewScreen(const GLuint uniform) const
{
  glUniformMatrix4fv(uniform, 1, GL_FALSE, &this->ViewScreenMatrix[0][0] );
}
