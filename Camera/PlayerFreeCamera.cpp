/*
 * File :
 *      ./Camera/PlayerFreeCamera.cpp
 *
 * Author : 
 *      Xonar <Paul le Roux>
 *
 * Description :
 *      Definitions of ./Camera/PlayerFreeCamera.h
 *      
 */
 
#include "PlayerFreeCamera.h"
#include "../Global.h"
#include <glm/gtx/rotate_vector.hpp>
#include "../Lib/Log.h"
#include "../Time/Time.h"
#include <cmath>

//Construct with FCamera pointer
FPlayerFreeCamera::FPlayerFreeCamera(FCamera* camera)
{
  this->camera = camera;
}

void FPlayerFreeCamera::update()
{
  //Camera State Variables
  glm::vec3 right;
  glm::vec3 forward;
  glm::vec3 pos;
  glm::vec3 up;

  //Movement Variables
  float speed = 4;
  float sprint = 8;
  float sensitivity = 0.2;
  float delta = FGetTimeChange();

  //Get Camera State
  forward = glm::normalize(this->camera->getDirection());
  pos = this->camera->getPosition();
  up = this->camera->getUp();
  right = glm::normalize(glm::cross(forward, up));
  
  //Movement Vector
  glm::vec3 mov(0,0,0);

  //Get Movement
  if(gKeyboard->isKeyDown(SDL_SCANCODE_A))
    mov -= right;
  if(gKeyboard->isKeyDown(SDL_SCANCODE_D))
    mov += right;
  if(gKeyboard->isKeyDown(SDL_SCANCODE_W))
    mov += forward;
  if(gKeyboard->isKeyDown(SDL_SCANCODE_S))
    mov -= forward; 

  //Handle Sprint
  if(gKeyboard->isKeyDown(SDL_SCANCODE_LSHIFT))
    speed = sprint;

  //Normalize movement to avoid diagonal speedup
  if(glm::length(mov)>0.1)
    mov = glm::normalize(mov);

  //Update Position
  this->camera->setPosition(pos+mov*speed*delta);

  //Handle Look about
  if(gMouse->isButtonDown(3))
  {
    glm::vec2 mouse = gMouse->getMovement() * sensitivity;

    //Get Current Rotation
    float theta = asin(glm::dot(up,forward));

    //Clamp theta rotation
    const float low_limit = -1;
    const float hi_limit = 1;
    float new_theta = std::min(std::max(theta+mouse.y, low_limit), hi_limit);

    //Do rotations
    forward = glm::rotate(forward, new_theta - theta, right);
    forward = glm::rotate(forward, mouse.x, up);

    //Update Direction
    this->camera->setDirection(forward);
  }
}
