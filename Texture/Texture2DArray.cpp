/*
 * File :
 *      ./Texture/Texture2DArray.cpp
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      Definitions of ./Texture/Texture.h::Texture2DArray
 */

#include "Texture.h"

#include <SDL2/SDL.h>

#include <iostream>

#include "../Graphics/Graphics.h"

FTexture2DArray::FTexture2DArray() 
{
  this->glTextureType = GL_TEXTURE_2D_ARRAY;
}

int FTexture2DArray::loadTextureFromSurface(const SDL_Surface * const surface[], const int num,
                                            const int max_width, const int max_height)
{
  if(surface)
  {
    this->width = surface[0]->w;
    this->height = surface[0]->h;

    GLenum format = (surface[0]->format->BytesPerPixel==3)?GL_RGB:GL_RGBA;

    glGenTextures( 1, &glTexture);
    glBindTexture( GL_TEXTURE_2D_ARRAY, glTexture);

    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, max_width, max_height, num, 0, format, 
                 GL_UNSIGNED_BYTE, NULL);
   
    for(int i = 0;i < num; i++)
    {
      glTexSubImage3D( GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, surface[i]->w, surface[i]->h, 
                       1, format, GL_UNSIGNED_BYTE, surface[i]->pixels);
    }

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  }
  else
  {
    std::cerr << "Tried creating texture from a empty surface!" << std::endl;
  }

  return 0;
}
