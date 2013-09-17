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

#include <glm/glm.hpp>

class FTexture
{
  private:
    GLuint glTexture;
    
    float width;
    float height;
  public:
    FTexture();
    ~FTexture();

    int loadTextureFromSurface(SDL_Surface* surface);
    int loadTextureFromFile(std::string file);

    void bindTexture(GLenum texture);

    int freeTexture();

    //TEST: Function to test image load capabilaties
    int blitToScreen(glm::vec2 pos);
};

#endif // _F_H_TEXTURE_
