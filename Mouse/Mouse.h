/*
 * File :
 *      ./Mouse/Mouse.h
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      DESCRIPTION
 */

#ifndef _F_H_MOUSE_
#define _F_H_MOUSE_

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

class FMouse
{
  private:
    Uint32 mouseStateCur, mouseStatePrev;
    int xCur, yCur, xPrev, yPrev;
  public:
    FMouse();

    void updateState();

    glm::vec2 getPos();
    glm::vec2 getMovement();

    bool isButtonPressed(int button);
    bool isButtonDown(int button);
    bool isButtonUp(int button);
    bool isButtonLifted(int button);
};

//Global Handle
extern FMouse *gMouse;

#endif // _F_H_MOUSE_
