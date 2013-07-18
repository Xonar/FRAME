/*
 * File :
 *      ./GUI/Font.h
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      The FFont class is a handler Font and Text
 */

#ifndef _F_H_FONT_
#define _F_H_FONT_

#include <SDL2/SDL_ttf.h>

#include <glm/glm.hpp>
#include <string>

#include "../Texture/Texture.h"

class FFont
{
  private:
    TTF_Font* sdlFont;
    unsigned int fontSize;

  public:
    FFont();

    int createFromTTF(std::string ttf,const unsigned int size);

    int drawText(std::string text,glm::vec2 pos);
};

#endif //_F_H_FONT_
