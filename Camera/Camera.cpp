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

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

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
    std::cerr << "Trying to use Camera before it's ready!" << std::endl;
    return 1;
  }

  return 0;
}

GLvoid FCamera::setViewPort(GLint x, GLint y, GLint w, GLint h)
{
  this->x = x;
  this->y = y;
  this->width = w;
  this->height = h;
  this->aspect = (float)w/h;
}

//Init 3D Ortho Matrix
GLint FCamera::InitOrthoMatrix( float left,float right,float bottom,float top, 
                                float near,float far)
{
  this->x = left;
  this->width = right - left;
  this->y = bottom;
  this->height = top - bottom;
  this->aspect = (float)w/h;

  //Create a allocate ViewScreen and WorlView Matrix
  glGenBuffers(1, &this->ubViewScreen);
  glBindBuffer(GL_UNIFORM_BUFFER, this->ubViewScreen);
  glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), NULL, GL_STREAM_DRAW);

  glGenBuffers(1, &this->ubWorldView);
  glBindBuffer(GL_UNIFORM_BUFFER, this->ubWorldView);
  glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), NULL, GL_STREAM_DRAW);

  this->updateViewScreenMatrix = true;

  this->ViewScreenMatrix = glm::ortho(left,right,bottom,top,near,far);

  this->ready = true;
  return 0;
}

//Init 2D Ortho Matrix
GLint FCamera::InitOrthoMatrix(float left,float right,float bottom,float top)
{
  this->x = left;
  this->width = right - left;
  this->y = bottom;
  this->height = top - bottom;
  this->aspect = (float)w/h;

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
GLint FCamera::InitProjectionMatrix(float fovy, float near, float far)
{
  //Create a allocate ViewScreen and WorlView Matrix
  glGenBuffers(1, &this->ubViewScreen);
  glBindBuffer(GL_UNIFORM_BUFFER, this->ubViewScreen);
  glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), NULL, GL_STREAM_DRAW);

  glGenBuffers(1, &this->ubWorldView);
  glBindBuffer(GL_UNIFORM_BUFFER, this->ubWorldView);
  glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), NULL, GL_STREAM_DRAW);

  this->updateViewScreenMatrix = true;

  this->ViewScreenMatrix = glm::perspective(fovy, this->aspect, near, far);

  this->ready = true;
  return 0;
}

GLvoid FCamera::setPosition(glm::vec3 pos)
{
  this->pos = pos;
  this->updateWorldViewMatrix = true;
}

GLvoid FCamera::lookAt(glm::vec3 lookAt)
{
  this->dir = lookAt - pos;
  this->updateWorldViewMatrix = true;
}

GLvoid FCamera::setDirection(glm::vec3 dir)
{
  this->dir = dir;
  this->updateWorldViewMatrix = true;
}

//Use Camera
void FCamera::setMatrixUniform(GLuint worldView, GLuint viewScreen)
{
  glViewport(this->x,this->y,this->width,this->height);

  this->updateUBO();

  glUniformMatrix4fv(worldView, 1, GL_FALSE, &this->WorldViewMatrix[0][0] );
  glUniformMatrix4fv(viewScreen, 1, GL_FALSE, &this->ViewScreenMatrix[0][0] );
}

void FCamera::setMatrixUniformWorldView(GLuint uniform)
{
  glViewport(this->x,this->y,this->width,this->height);
  
  this->updateUBO();

  glUniformMatrix4fv(uniform, 1, GL_FALSE, &this->WorldViewMatrix[0][0] );
}

void FCamera::setMatrixUniformViewScreen(GLuint uniform)
{
  glViewport(this->x,this->y,this->width,this->height);
  
  this->updateUBO();

  glUniformMatrix4fv(uniform, 1, GL_FALSE, &this->ViewScreenMatrix[0][0] );
}
