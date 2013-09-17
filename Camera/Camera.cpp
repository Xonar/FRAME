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
  this->ready = false;

  this->pos = glm::vec3(0,0,0);
  this->dir = glm::vec3(0,0,1);

  this->ubo = 0;

  glGenBuffers(1, &this->ubo);
}

FCamera::~FCamera()
{
  glDeleteBuffers(1, &this->ubo);
  this->ubo = 0;
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
      
      glBindBuffer(GL_UNIFORM_BUFFER, this->ubo);

      glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &this->WorldViewMatrix[0][0]);
    }

    //Only update if it's neccesary
    if(this->updateViewScreenMatrix)
    {
      glBindBuffer(GL_UNIFORM_BUFFER, this->ubo);

      glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4),
                        &this->ViewScreenMatrix[0][0]);
    }
  }
  else
  {
    std::cerr << "Trying to use Camera before it's ready!" << std::endl;
    return 1;
  }

  return 0;
}

//Init 3D Ortho Matrix
GLint FCamera::InitOrthoMatrix( float left,float right,float bottom,float top, 
                                float near,float far)
{
  this->updateViewScreenMatrix = true;

  this->ViewScreenMatrix = glm::ortho(left,right,bottom,top,near,far);

  this->ready = true;
  return 0;
}

//Init 2D Ortho Matrix
GLint FCamera::InitOrthoMatrix(float left,float right,float bottom,float top)
{
  this->updateViewScreenMatrix = true;

  this->ViewScreenMatrix = glm::ortho(left,right,bottom,top);

  this->ready = true;
  return 0;
}

//Init Projection Matrix
GLint FCamera::InitProjectionMatrix(float fovy, float near, float far)
{
  this->updateViewScreenMatrix = true;

  this->ViewScreenMatrix = glm::perspective(fovy, this->aspect, near, far);

  this->ready = true;
  return 0;
}

//Use Camera
void FCamera::bindMatrixUniformBlock()
{
  glViewport(this->x,this->y,this->width,this->height);

  this->updateUBO();

  int curProg;

  glGetIntegerv(GL_CURRENT_PROGRAM, &curProg);

  glBindBufferBase(GL_UNIFORM_BUFFER, F_UNIFORM_BLOCK_CAMERA , this->ubo);
}

void FCamera::bindMatrixUniformWorldView(GLuint uniform)
{
  glViewport(this->x,this->y,this->width,this->height);
  
  this->updateUBO();

  int curProg;

  glGetIntegerv(GL_CURRENT_PROGRAM, &curProg);

  glUniformMatrix4fv(uniform, 1, GL_FALSE, &this->WorldViewMatrix[0][0] );
}

void FCamera::bindMatrixUniformViewScreen(GLuint uniform)
{
  glViewport(this->x,this->y,this->width,this->height);
  
  this->updateUBO();

  int curProg;

  glGetIntegerv(GL_CURRENT_PROGRAM, &curProg);

  glUniformMatrix4fv(uniform, 1, GL_FALSE, &this->ViewScreenMatrix[0][0] );
}
