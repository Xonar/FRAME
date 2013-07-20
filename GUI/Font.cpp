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

#include <algorithm>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

FFont::FFont()
{
  //Constructor
  this->sdlFont = NULL;

  this->fontSize = 18;

  this->chars_start = 32;
  this->chars_end = 128;
  this->chars = NULL;
}

GLint FFont::createFromTTF(std::string ttf, const unsigned int size)
{
  this->sdlFont = TTF_OpenFont(ttf.c_str(), size);
  this->fontSize = size;
  
  if(!sdlFont)
  {
    std::cerr << "Failed loading Font (\"" << ttf << "\")" << std::endl;
  }

  chars = new FGlyph[chars_end];

  GLint sofar=0,gminy=0;

  std::string text= "";

  for(GLint i = chars_start; i < chars_end - chars_start; i++)
  {
    if(TTF_GlyphIsProvided(this->sdlFont, i))
    {
      GLint minx,maxx,miny,maxy,adv;
      TTF_GlyphMetrics(this->sdlFont, i, &minx, &maxx, &miny, &maxy, &adv);
      gminy = std::min(gminy,miny);

      chars[(int)i].adv.x = adv;
      chars[(int)i].adv.y = 0;

      chars[(int)i].dim.x = maxx - minx;
      chars[(int)i].dim.y = maxy - miny;

      chars[(int)i].pos.y = miny;
      chars[(int)i].pos.x = sofar;

      sofar += chars[(int)i].dim.x;
      text += i;
    }
    else
    {
      chars[(int)i].pos = chars[(int)i].dim = chars[(int)i].off = 
                          chars[(int)i].adv = glm::vec2(0.f,0.f);
    }
  }

  for(int i = chars_start; i < chars_end - chars_start; i++)
  {
   chars[i].pos.y -= gminy; 
  }


  TTF_SetFontKerning(this->sdlFont,0);

  SDL_Surface* surface = TTF_RenderText_Blended(this->sdlFont, text.c_str(), {255,255,255});
  
  this->texture = FTexture();
  texture.loadTextureFromSurface(surface);
  
  SDL_FreeSurface(surface);

  return 0; 
}

GLint FFont::drawFontTexture(glm::vec2 pos)
{
  this->texture.blitToScreen(pos);

  return 0;
}

GLint FFont::drawText(std::string text,glm::vec2 pos)
{
  SDL_Surface* s = TTF_RenderText_Blended(this->sdlFont, text.c_str(), {255,0,255,255} );
  FTexture t;
  t.loadTextureFromSurface(s);
  t.blitToScreen(pos);
  t.~FTexture();
  SDL_FreeSurface(s);

  return 0;
}
