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

void FFontHandler::Init(FFont &font)
{
  this->font = font;
}

void FFontHandler::addText(std::vector<FTextVertex> data)
{
  this->charData.insert(this->charData.end(), data.begin(), data.end());
}

std::vector<FTextVertex>& FFontHandler::getCharData()
{
  return this->charData;
}

int FFontHandler::getCharNum()
{
  return this->charData.size() / 6;
}

void FFontHandler::clearCharData()
{
  this->charData.clear();
}

void FFontHandler::ready(GLuint uniformTexture)
{
  //TODO Other Uniforms Aswel
  font.bindTexture(GL_TEXTURE0);
}
