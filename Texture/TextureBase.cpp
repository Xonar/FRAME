/*
 * File :
 *      ./Texture/TextureBase.cpp
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      Definitions of ./Texture/Texture.h::TextureBase
 */

#include "Texture.h"

FTextureBase::FTextureBase()
{
  this->glTexture = 0;
  this->width = 0;
  this->height = 0;
}

void FTextureBase::freeTexture()
{
  if(this->glTexture)
    glDeleteTextures( 1, &this->glTexture );
  this->glTexture = 0;
}

void FTextureBase::bindTexture(GLenum texture)
{
  glActiveTexture(texture);
  glBindTexture(this->glTextureType, this->glTexture);
}
