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

class FTexture2D
{
  private:
    GLuint glTexture;
    
    float width;
    float height;
  public:
    FTexture2D();
    ~FTexture2D();

    int loadTextureFromSurface(SDL_Surface* surface);
    int loadTextureFromFile(std::string file);

    void bindTexture(GLenum texture);

    int freeTexture();
};

class FTexture2DArray
{
  private:
    GLuint glTexture;
    
    float width;
    float height;
  public:
    FTexture2DArray();
    ~FTexture2DArray();

    int loadTextureFromSurface(SDL_Surface *surface[], int num, int max_width, int max_height);

    void bindTexture(GLenum texture);

    int freeTexture();
};
#endif // _F_H_TEXTURE_
