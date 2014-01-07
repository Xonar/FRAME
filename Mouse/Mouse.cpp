/*
 * File :
 *      ./Mouse/Mouse.cpp
 *
 * Author : 
 *      Xonar <Paul le Roux>
 *
 * Description :
 *      Definitions of ./Mouse/Mouse.h
 *      
 */
 
#include "Mouse.h"
#include <algorithm>

FMouse::FMouse()
{
    this->mouseStateCur = SDL_GetMouseState(&xCur, &yCur);

    this->mouseStatePrev = this->mouseStateCur;
    this->xPrev = this->xCur;
    this->yPrev = this->yCur;
}

void FMouse::updateState()
{
  this->mouseStatePrev = this->mouseStateCur;
  this->xPrev = this->xCur;
  this->yPrev = this->yCur;

  this->mouseStateCur = SDL_GetMouseState(&xCur, &yCur);
}

glm::vec2 FMouse::getPos()
{
  return glm::vec2((float)xCur, (float)xPrev);
}

glm::vec2 FMouse::getMovement()
{
  return glm::vec2((float)(xPrev - xCur), (float)(yPrev - yCur));
}

bool FMouse::isButtonPressed(int button)
{
  return (mouseStateCur&SDL_BUTTON(button)) && ! (mouseStatePrev&SDL_BUTTON(button));
}

bool FMouse::isButtonDown(int button)
{
  return mouseStateCur&SDL_BUTTON(button);
}

bool FMouse::isButtonUp(int button)
{
  return !mouseStateCur&SDL_BUTTON(button);
}

bool FMouse::isButtonLifted(int button)
{
  return ! (mouseStateCur&SDL_BUTTON(button)) && (mouseStatePrev&SDL_BUTTON(button));
}
