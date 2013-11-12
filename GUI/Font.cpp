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
#include "../Graphics/Graphics.h"
#include "../Lib/FGLext.h"
#include "../Global.h"
#include "../Lib/Log.h"

#include <vector>

#include <algorithm>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_ttf.h>

FFont::FFont()
{
  //Constructor
  this->sdlFont = NULL;

  this->fontSize = 18;

  this->chars_start = 32;
  this->chars_end = 128;
  this->chars = NULL;

  for(int i = 0;i < 256; i++)
    charMap[i] = -1;

  this->fontID = -1;
}

FFont::~FFont()
{
  if(chars)
  {
    delete[] chars;
    chars = NULL;
  }

  if(sdlFont)
    TTF_CloseFont(sdlFont);
  sdlFont = NULL;
}

GLint FFont::createFromTTF(const std::string &ttf, const unsigned int size)
{
  this->sdlFont = TTF_OpenFont(ttf.c_str(), size);
  this->fontSize = size;
  
  if(!sdlFont)
  {
    gLogw << "Failed loading Font (\"" << ttf << "\")" << std::endl;
    return 1;
  }

  chars = new FGlyph[chars_end - chars_start];
  SDL_Surface *surfaces[chars_end - chars_start];

  int index = 0;
  char tmpString[2] = {0};

  int max_height = 0, max_width = 0;

  for(GLint i = chars_start; i < chars_end; i++)
  {
    if(TTF_GlyphIsProvided(this->sdlFont, i) && i != ' ') //Don't Render Space
    {
      GLint minx,maxx,miny,maxy,adv;
      
      TTF_GlyphMetrics(this->sdlFont, i, &minx, &maxx, &miny, &maxy, &adv);

      tmpString[0] = (char)i;

      surfaces[index] = TTF_RenderText_Blended(this->sdlFont, tmpString, {255, 255, 255, 255});
      
      chars[index].adv.x = adv;
      chars[index].adv.y = 0.f;

      chars[index].dim.x = surfaces[index]->w;
      chars[index].dim.y = surfaces[index]->h;
      
      //Offset is alreadt applied
      chars[index].off.y = 0/*- miny*/;
      chars[index].off.x = 0/*  minx*/;

      charMap[i] = index;
      max_height = std::max(max_height, surfaces[index]->h);
      max_width = std::max(max_width, surfaces[index]->w);

      index++;
    }
  }

  twidth = max_width;
  theight = max_height;

  this->textures = new FTexture2DArray();
  textures->loadTextureFromSurface(surfaces, index, max_width, max_height);
  
  for(int i = 0;i < index;i++)
    SDL_FreeSurface(surfaces[i]);
  
  return 0;
}

void FFont::generateStringVertexData(const std::string &text, 
          const glm::vec2 &off, std::vector<FVertexText> &out) const
{
  glm::vec2 cpos = off;

  FVertexText bl,br,tl,tr;

  for(const GLint &i : text)
  {
    int index = charMap[i];
    if(index >= 0)
    {
      float texx = chars[index].dim.x/this->twidth;
      float texy = chars[index].dim.y/this->theight;

      bl.tex = glm::vec2(0.f, 1-0.f);
      tl.tex = glm::vec2(0.f, 1-texy);
      br.tex = glm::vec2(texx, 1-0.f);
      tr.tex = glm::vec2(texx, 1-texy) ;

      bl.index = br.index = tr.index = tl.index = index;

      bl.pos = br.pos = tl.pos = tr.pos = cpos - chars[index].off;

      tr.pos += chars[index].dim;
      tl.pos.y += chars[index].dim.y;
      br.pos.x += chars[index].dim.x;

      out.push_back(bl);
      out.push_back(br);
      out.push_back(tr);
      out.push_back(tl);

      cpos += chars[index].adv;
    }
    else if(i == ' ')
      cpos.x += fontSize / 4;
  }
}

void FFont::bindTexture(const GLenum textureUnit) const
{
  textures->bindTexture(textureUnit);
}

GLvoid FFont::drawText(const std::string &text,const glm::vec2 &pos) const
{
  gFontEngine->addText(this->fontID, text, pos);
}
