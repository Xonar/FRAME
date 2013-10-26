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

#include <vector>

#include <iostream>

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

  //Generate Vertex Array for Output
  glGenVertexArrays(1, &this->vao);
  glGenBuffers(1, &this->vbo);

  for(int i = 0;i < 256; i++)
    charMap[i] = -1;
}

FFont::~FFont()
{
  delete[] chars;

  glDeleteVertexArrays(1, &this->vao);

  if(sdlFont)
    TTF_CloseFont(sdlFont);
  sdlFont = NULL;
}

GLint FFont::createFromTTF(std::string ttf, const unsigned int size)
{
  this->sdlFont = TTF_OpenFont(ttf.c_str(), size);
  this->fontSize = size;
  
  if(!sdlFont)
  {
    std::cerr << "Failed loading Font (\"" << ttf << "\")" << std::endl;
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
      
      chars[index].adv.x = adv - minx;
      chars[index].adv.y = 0.f;

      chars[index].dim.x = surfaces[index]->w;
      chars[index].dim.y = surfaces[index]->h;

      chars[index].off.y = 0/*- miny*/;
      chars[index].off.x = minx;

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

std::vector<FTextVertex> FFont::generateStringVertexData(std::string text, glm::vec2 off)
{
  std::vector<FTextVertex> out;

  glm::vec2 cpos = off;

  FTextVertex bl,br,tl,tr;

  for(const GLint &i : text)
  {
    if(charMap[i] >= 0)
    {
      float texx = chars[charMap[i]].dim.x/this->twidth;
      float texy = chars[charMap[i]].dim.y/this->theight;

      bl.tex = glm::vec2(0.f, 1-0.f);
      tl.tex = glm::vec2(0.f, 1-texy);
      br.tex = glm::vec2(texx, 1-0.f);
      tr.tex = glm::vec2(texx, 1-texy) ;

      bl.index = br.index = tr.index = tl.index = charMap[i];

      bl.pos = br.pos = tl.pos = tr.pos = cpos - chars[charMap[i]].off;

      tr.pos += chars[charMap[i]].dim;
      tl.pos.y += chars[charMap[i]].dim.y;
      br.pos.x += chars[charMap[i]].dim.x;

      out.push_back(bl);
      out.push_back(tl);
      out.push_back(tr);

      out.push_back(bl);
      out.push_back(tr);
      out.push_back(br);

      cpos += chars[charMap[i]].adv;
    }
    else if(i == ' ')
      cpos.x += fontSize /4.0f;
  }

  return out;
}

GLint FFont::drawText(std::string text,glm::vec2 pos)
{
  textures->bindTexture( GL_TEXTURE0 );

  std::vector<FTextVertex> data = generateStringVertexData(text, pos);

  glBindVertexArray(this->vao);
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

  glVertexAttribPointers(F_VERTEX_TEXT);
  glEnableVertexAttribs(F_VERTEX_TEXT);

  glBufferData(GL_ARRAY_BUFFER, sizeof(data[0]) * data.size(), &data[0], GL_DYNAMIC_DRAW);
  
  textures->bindTexture(GL_TEXTURE0);
  
  glDrawArrays(GL_TRIANGLES, 0, data.size());
  
  data.clear();
  
  return 0;
}
