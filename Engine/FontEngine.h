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

#ifndef _F_H_ENGINE_FONT_
#define _F_H_ENGINE_FONT_

#include <SDL2\SDL_opengl.h>

#include <vector>

#include "../GUI/Font.h"
#include "../Shader/Shader.h"
#include "../Camera/Camera.h"
#include "../Container/Container.h"

class FontEngine
{
  private:
    GLuint vao;
    GLuint vbo;
    GLuint ibo;

    GLuint numVertices;
    std::vector<FTextVertex> charData;

    GLuint numFonts;
    std::vector<FFontHandler> fontHandler;

    FShader fontShader;
    FCamera fontCamera;
  public:
    FontEngine();

    GLuint addFont(FFont &font);
    void addText(GLint font, std:vector<FTextVertex> data);

    void render();
}

#endif //_F_H_ENGINE_FONT_
