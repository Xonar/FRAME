/*
 * File :
 *      ./Engine/FontEngine.cpp
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      Definitions of ./Engine/FontEngine.h
 */

#include "FontEngine.h"

#include "../Global.h"

#include "../Graphics/Graphics.h"
#include "../Lib/FGLext.h"

#include <iostream>

FFontEngine::FFontEngine()
{
  this->ibo = this->vbo = this->vao = this->numFonts = 0;

  //Init Font Shader
  this->fontShader = FShader();

  this->fontShader.loadShader("Shader/FX/Text/text.glvs",GL_VERTEX_SHADER);
  this->fontShader.loadShader("Shader/FX/Text/text.glfs",GL_FRAGMENT_SHADER);

  this->fontShader.loadProgram();

  this->uniformOrthoMatrix = glGetUniformLocation(this->fontShader.getProgram(), "OrthoMatrix");
  this->uniformFontTexture = glGetUniformLocation(this->fontShader.getProgram(), "Texture");
  
  //Init Font Ortho Matrix
  fontCamera = FCamera();

  fontCamera.InitOrthoMatrix(0,gWindow->getWindowWidth(),0,gWindow->getWindowHeight());

  //OpenGL Buffers
  glGenVertexArrays(1, &this->vao);
  glGenBuffers(1, &this->vbo);
  glGenBuffers(1, &this->ibo);

  //Setup VAO
  glBindVertexArray(this->vao);
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,this->ibo);

  glVertexAttribPointers(F_VERTEX_TEXT);
  glEnableVertexAttribs(F_VERTEX_TEXT);

  //Setup IBO
  GLuint* indices = new GLuint[F_FONT_ENGINE_MAX_CHARACTERS_PER_DRAW * 6]; 
  
  for(int i = 0;i < F_FONT_ENGINE_MAX_CHARACTERS_PER_DRAW; i++)
  {
    indices[i*6 + 0] = i*4 + 0;
    indices[i*6 + 1] = i*4 + 1;
    indices[i*6 + 2] = i*4 + 2;

    indices[i*6 + 3] = i*4 + 0;
    indices[i*6 + 4] = i*4 + 3;
    indices[i*6 + 5] = i*4 + 2;
  }

  glBufferData(GL_ELEMENT_ARRAY_BUFFER, F_FONT_ENGINE_MAX_CHARACTERS_PER_DRAW * 6 * sizeof(GLuint),
               indices, GL_STATIC_DRAW);

  delete[] indices;
}

void FFontEngine::addFont(FFont *font)
{
  FFontHandler newHandler = FFontHandler();
  
  font->setFontID(fontHandler.size());

  newHandler.Init(font);

  fontHandler.push_back(newHandler);
}

void FFontEngine::addText(const GLint &font, const std::string &text, const glm::vec2 &pos)
{
  fontHandler[font].addText(text,pos);
}

void FFontEngine::render()
{
  //Disable Culling and Depth Testing
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);

  std::vector<FTextVertex> vertices;

  for(FFontHandler &it : fontHandler)
  {
    std::vector<FTextVertex>& data = it.getCharData();
    vertices.insert(vertices.end(), data.begin(), data.end() );
  }

  fontShader.bind();

  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(FTextVertex) * vertices.size(), &vertices[0],
                   GL_DYNAMIC_DRAW);

  //Bind OrthoMatrix
  fontCamera.setMatrixUniformViewScreen(uniformOrthoMatrix);

  GLint numChars = 0;

  for(FFontHandler &it : fontHandler)
  {
    //glDrawArrays(GL_TRIANGLES, 0, vertices.size() - 1);

    it.ready(this->uniformFontTexture);

    int size = it.getCharNum();

    for(; size > F_FONT_ENGINE_MAX_CHARACTERS_PER_DRAW;)
    {
      glDrawElementsBaseVertex(GL_TRIANGLES, F_FONT_ENGINE_MAX_CHARACTERS_PER_DRAW * 6,
                               GL_UNSIGNED_INT, NULL, numChars * 4);

      size -= F_FONT_ENGINE_MAX_CHARACTERS_PER_DRAW;
      numChars += F_FONT_ENGINE_MAX_CHARACTERS_PER_DRAW;
    }

    glDrawElementsBaseVertex(GL_TRIANGLES, size * 6,
                             GL_UNSIGNED_INT, NULL, numChars * 4);
    
    numChars += size;

    it.clearCharData();
  }
}
