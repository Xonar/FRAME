/*
 * File :
 *      ./Texture/Texture.cpp
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      Definitions of ./Texture/Texture.h
 */

#include "Texture.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <glm/glm.hpp>

#include <iostream>

FTexture::FTexture() 
{
  this->glTexture = 0;
  this->width = 0;
  this->height = 0;
}

FTexture::~FTexture()
{
  if(glTexture)
  this->freeTexture();
}

int FTexture::freeTexture()
{
  glDeleteTextures( 1, &this->glTexture );
  this->glTexture = 0;
  return 0;
}

int FTexture::loadTextureFromSurface(SDL_Surface* surface)
{
  if(surface)
  {
    this->width = surface->w;
    this->height = surface->h;

    glGenTextures( 1, &glTexture);
    glBindTexture( GL_TEXTURE_2D, glTexture);
    glTexImage2D( GL_TEXTURE_2D, 0, surface->format->BytesPerPixel, width, height, 0,
        (surface->format->BytesPerPixel==3)?GL_RGB:GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels );
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  }
  else
  {
    std::cerr << "Tried creating texture from a empty surface!" << std::endl;
  }

  return 0;
}

int FTexture::loadTextureFromFile(std::string file)
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
    std::cerr << "Failed loading Image from file (\"" << file << "\")" << std::endl;
    return 1;
  }
}

//TEST: This function is used to test the image load capabilaties and should NOT be used
//TODO: Remove after implementing sufficient other functions/methods/classes

int FTexture::blitToScreen(glm::vec2 pos)
{
  glLoadIdentity();
  glTranslatef( pos.x, pos.y, 0.f );

  glBindTexture (GL_TEXTURE_2D, this->glTexture);

  glBegin( GL_QUADS );
    glColor3f(1.f,1.f,1.f);
    glTexCoord2f( 0.f, 0.f ); glVertex2f( 0.f, 0.f ); 
    glTexCoord2f( 1.f, 0.f ); glVertex2f( this->width, 0.f );
    glTexCoord2f( 1.f, 1.f ); glVertex2f( this->width, this->height );
    glTexCoord2f( 0.f, 1.f ); glVertex2f( 0.f, this->height );
  glEnd();

  return 0;
}
