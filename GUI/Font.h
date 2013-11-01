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

#include <vector>

#include "../Container/Container.h"
#include "../Texture/Texture.h"

class FFont
{
  private:
    struct FGlyph
    {
      glm::vec2 dim; //Dimensions of Char
      glm::vec2 adv; //Cursor movement
      glm::vec2 off; //Cursor offset in texture
    };
    
    GLint chars_start;
    GLint chars_end;
    FGlyph *chars;

    TTF_Font* sdlFont;
    FTexture2DArray* textures;

    int charMap[256];

    GLfloat twidth;
    GLfloat theight;

    GLuint fontSize;

    GLint fontID;
  public:
    FFont();
    ~FFont();

    GLint createFromTTF(const std::string &ttf,const unsigned int size);
    GLint createFromDistanceFieldFile(const std::string &textureFile, const std::string &glyphFile);

    GLvoid drawText(const std::string &text,const glm::vec2 &pos) const;

    GLvoid bindTexture(const GLenum textureUnit) const;

    GLvoid setFontID(const GLint fontID) { this->fontID = fontID; }
    
    void generateStringVertexData(const std::string &text, 
          const glm::vec2 &off, std::vector<FTextVertex> &out) const;
};

#endif //_F_H_FONT_
