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

    void Init(FFont * const font);

    void addText(const std::string &text, const glm::vec2 &pos);

    const std::vector<FTextVertex>& getCharData() const;
    int getCharNum() const;
    void clearCharData();

    void ready(const GLuint uniformTexture) const;
};

#endif //_F_H_FONT_HANDLER_
