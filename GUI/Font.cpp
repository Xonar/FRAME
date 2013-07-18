/*
 * File :
 *      ./GUI/Font.cpp
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      Definitions of ./GUI/Font.h
 */

#include "Font.h"
#include <vector>

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

FFont::FFont()
{
  //Constructor
  this->sdlFont = NULL;
}

int FFont::createFromTTF(std::string ttf, const unsigned int size)
{
  this->sdlFont = TTF_OpenFont(ttf.c_str(), size);
  this->fontSize = size;
  
  if(!sdlFont)
  {
    std::cerr << "Failed loading Font (\"" << ttf << "\")" << std::endl;
  }

  return 0; 
}

int FFont::drawText(std::string text,glm::vec2 pos)
{
  SDL_Surface* s = TTF_RenderText_Blended(this->sdlFont, text.c_str(), {255,0,255,255} );
  FTexture t;
  t.loadTextureFromSurface(s);
  t.blitToScreen(pos);
  t.~FTexture();
  SDL_FreeSurface(s);

  return 0;
}
