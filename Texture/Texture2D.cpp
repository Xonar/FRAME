/*
 * File :
 *      ./Texture/Texture.cpp
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      Definitions of ./Texture/Texture.h::FTexture2D
 */

#include "Texture.h"
#include "../Container/Container.h"
#include "../Graphics/Graphics.h"
#include "../Lib/Log.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

FTexture2D::FTexture2D() 
{
  this->glTextureType = GL_TEXTURE_2D;
}

int FTexture2D::loadTextureFromSurface(const SDL_Surface* const surface)
{
  if(surface)
  {
    this->width = surface->w;
    this->height = surface->h;

    GLenum format = (surface->format->BytesPerPixel==3)?GL_RGB:GL_RGBA;

    glGenTextures( 1, &glTexture);
    glBindTexture( GL_TEXTURE_2D, glTexture);
    glTexImage2D( GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE,
                  surface->pixels );
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  }
  else
  {
    gLogw << "Tried creating texture from a empty surface!" << std::endl;
  }

  return 0;
}

int FTexture2D::loadTextureFromFile(const std::string &file)
{
  SDL_Surface *surface;

  if( (surface = IMG_Load(file.c_str()) ) )
  {
    loadTextureFromSurface(surface);
  }

  if(surface)
  {
    SDL_FreeSurface(surface);
    return 0;
  }
  else
  {
    gLoge << "Failed loading Image from file (\"" << file << "\")" << std::endl;
    return 1;
  }
}
