/*
 * File :
 *      ./Keyboard/Keyboard.cpp
 *
 * Author : 
 *      Xonar <Paul le Roux>
 *
 * Description :
 *      Definitions of ./Keyboard/Keyboard.h
 *      
 */
 
#include "Keyboard.h"
#include <algorithm>

FKeyboard::FKeyboard()
{
  int num;

  SDL_GetKeyboardState(&num);

  this->keyCur = new Uint8[num];
  this->keyPrev = new Uint8[num];
}

FKeyboard::~FKeyboard()
{
  delete[] this->keyPrev;
  delete[] this->keyCur;
}

void FKeyboard::updateState()
{
  static int num;
  static const Uint8 *state = SDL_GetKeyboardState(&num);
  std::swap(this->keyCur, this->keyPrev);
  std::copy(state, state+num, this->keyCur);
}

bool FKeyboard::isKeyPressed(GLuint key)
{
  return this->keyCur[ key ] && !this->keyPrev[ key ];
}

bool FKeyboard::isKeyLifted(GLuint key)
{
  return !this->keyCur[ key ] && this->keyPrev[ key ];
}

bool FKeyboard::isKeyDown(GLuint key)
{
  return this->keyCur[ key ];
}

bool FKeyboard::isKeyUp(GLuint key)
{
  return !this->keyCur[ key ];
}
