/*
 * File :
 *      ./Keyboard/Keyboard.h
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      DESCRIPTION
 */

#ifndef _F_H_KEYBOARD_
#define _F_H_KEYBOARD_

#include "../Graphics/Graphics.h"
#include <SDL2/SDL_image.h>

class FKeyboard
{
  private:
    Uint8* keyCur;
    Uint8* keyPrev;
  public:
    FKeyboard();
    ~FKeyboard();

    void updateState();

    bool isKeyPressed(GLuint key);
    bool isKeyLifted(GLuint key);
    bool isKeyDown(GLuint key);
    bool isKeyUp(GLuint key);
};

#endif // _F_H_KEYBOARD_
