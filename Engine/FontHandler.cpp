/*
 * File :
 *      ./Engine/FontEngine.cpp
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      Definitions of ./Engine/FontHandler.h
 */

#include "FontHandler.h"

FFontHandler::FFontHandler()
{
  //Nothing to be done
}

void FFontHandler::Init(FFont *const font)
{
  this->font = font;
}

void FFontHandler::addText(const std::string &text, const glm::vec2 &pos)
{
  this->font->generateStringVertexData(text, pos, this->charData);
}

std::vector<FTextVertex>& FFontHandler::getCharData()
{
  return this->charData;
}

int FFontHandler::getCharNum()
{
  return this->charData.size() / 4;
}

void FFontHandler::clearCharData()
{
  this->charData.clear();
}

void FFontHandler::ready(const GLuint uniformTexture)
{
  //TODO Other Uniforms Aswel
  font->bindTexture(GL_TEXTURE0);
}
