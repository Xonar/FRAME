/*
 * File :
 *      ./Texture/Texture.h
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      The FTexture is a handler for all textures
 */

#ifndef _F_H_TEXTURE_
#define _F_H_TEXTURE_

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

class FTextureBase
{
  protected:
    GLuint glTexture;

    float width;
    float height;

    GLenum glTextureType;
  public:
    FTextureBase();
    ~FTextureBase();

    void bindTexture(const GLenum texture);

    void freeTexture();
};

class FTexture2D : public FTextureBase
{
  public:
    FTexture2D();
    ~FTexture2D() {};

    int loadTextureFromSurface(const SDL_Surface* const surface);
    int loadTextureFromFile(const std::string &file);
};

class FTexture2DArray : public FTextureBase
{
  public:
    FTexture2DArray();
    ~FTexture2DArray() {};

    int loadTextureFromSurface(const SDL_Surface * const surface[], const int num, const int max_width,
                               const int max_height);
};
#endif // _F_H_TEXTURE_
