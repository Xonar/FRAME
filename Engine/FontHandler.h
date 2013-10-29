/*
 * File :
 *      ./Engine/FontEngine.h
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      Font Engine that handles rendering of text.
 */

#ifndef _F_H_FONT_HANDLER_
#define _F_H_FONT_HANDLER_

#include "../GUI/Font.h"
#include "../Container/Container.h"
#include <vector>

class FFontHandler
{
  private:
    FFont *font;

    std::vector<FTextVertex> charData;
  public:
    FFontHandler();

    void Init(FFont *font);

    void addText(const std::string &text, const glm::vec2 &pos);

    std::vector<FTextVertex>& getCharData();
    int getCharNum();
    void clearCharData();

    void ready(const GLuint uniformTexture);
};

#endif //_F_H_FONT_HANDLER_
