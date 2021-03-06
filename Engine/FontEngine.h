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

class FFontEngine;

#include <vector>
#include <list>

#include "../GUI/Font.h"
#include "../Engine/FontHandler.h"
#include "../Shader/Shader.h"
#include "../Camera/Camera.h"
#include "../Container/Container.h"
#include "../Graphics/Graphics.h"

#define F_FONT_ENGINE_MAX_CHARACTERS_PER_DRAW 512

class FFontEngine
{
  private:
    GLuint vao;
    GLuint vbo;
    GLuint ibo;

    std::vector<GLuint> indices;

    GLuint numFonts;
    std::vector<FFontHandler> fontHandler;

    FShader fontShader;
    FCamera fontCamera;

    GLuint uniformOrthoMatrix;
    GLuint uniformFontTexture;
  public:
    FFontEngine();

    void addFont(FFont * const font);
    void addText(const GLint font, const std::string &text, const glm::vec2 &pos);

    void render();
};

//Global Handle
extern FFontEngine *gFontEngine;

#endif //_F_H_ENGINE_FONT_
