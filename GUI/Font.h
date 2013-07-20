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
    struct FGlyph
    {
      glm::vec2 pos; //Position in Texture
      glm::vec2 dim; //Dimensions of Char
      glm::vec2 adv; //Cursor movement
      glm::vec2 off; //Cursor offset in texture
    };
    
    GLint chars_start;
    GLint chars_end;
    FGlyph *chars;

    TTF_Font* sdlFont;
    FTexture texture;

    GLuint fontSize;
  public:
    FFont();

    GLint createFromTTF(std::string ttf,const unsigned int size);

    GLint drawFontTexture(glm::vec2 pos);
    GLint drawText(std::string text,glm::vec2 pos);
};

#endif //_F_H_FONT_
