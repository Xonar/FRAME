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

    indices[i*6 + 3] = i*4 + 2;
    indices[i*6 + 4] = i*4 + 3;
    indices[i*6 + 5] = i*4 + 0;
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

void FFontEngine::addText(GLint font, std::vector<FTextVertex> data)
{
  numVertices += data.size();
  fontHandler[font].addText(data);
}

void FFontEngine::render()
{
  std::vector<FTextVertex> vertices;
  vertices.reserve(numVertices);

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

  numVertices = 0;

  //glDrawArrays(GL_TRIANGLES, 0, vertices.size());

  for(FFontHandler &it : fontHandler)
  {
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    it.ready(this->uniformFontTexture);

    int size = it.getCharNum() * 6;

    for(; size > F_FONT_ENGINE_MAX_CHARACTERS_PER_DRAW*6;)
    {
      glDrawElementsBaseVertex(GL_TRIANGLES, F_FONT_ENGINE_MAX_CHARACTERS_PER_DRAW * 6,
                               GL_UNSIGNED_BYTE, NULL, numVertices);

      size -= F_FONT_ENGINE_MAX_CHARACTERS_PER_DRAW * 6;
      numVertices += F_FONT_ENGINE_MAX_CHARACTERS_PER_DRAW * 6;
    }

    glDrawElementsBaseVertex(GL_TRIANGLES, size,
                             GL_UNSIGNED_BYTE, NULL, numVertices);
    
    numVertices += size;

    it.clearCharData();
  }
}
