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

#include "../Graphics/Graphics.h"
#include "../Lib/FGLext.h"
#include "../Shader/ShaderManager.h"
#include "../Window/Window.h"

FFontEngine::FFontEngine()
{
  this->ibo = this->vbo = this->vao = this->numFonts = 0;

  //Init Font Shader
  this->fontShader = *gShaderManager->loadShader("FontShader", "Shader/FX/Text/text.glvs", 
                                                            "Shader/FX/Text/text.glfs");

  this->uniformFontTexture = glGetUniformLocation(this->fontShader.getProgram(), "Texture");
  
  //Init Font Ortho Matrix
  fontCamera = FCamera();

  fontCamera.InitOrthoMatrix(0,gWindow->getWindowWidth(),0,gWindow->getWindowHeight());

  this->uniformOrthoMatrix = glGetUniformLocation(this->fontShader.getProgram(), "Ortho");

  //Set Ortho Matrix Value
  fontShader.bind();
  fontCamera.use();
  fontCamera.setMatrixUniform(uniformOrthoMatrix);

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

void FFontEngine::addFont(FFont * const font)
{
  FFontHandler newHandler = FFontHandler();
  
  font->setFontID(fontHandler.size());

  newHandler.Init(font);

  fontHandler.push_back(newHandler);
}

void FFontEngine::addText(const GLint font, const std::string &text, const glm::vec2 &pos)
{
  fontHandler[font].addText(text,pos);
}

void FFontEngine::render()
{
  //Set default framebuffer
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

  //Enable Blend States
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  //Disable Culling and Depth Testing
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);

  std::vector<FVertexText> vertices;

  for(const FFontHandler &it : fontHandler)
  {
    const std::vector<FVertexText>& data = it.getCharData();
    vertices.insert(vertices.end(), data.begin(), data.end() );
  }

  fontShader.bind();

  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(FVertexText) * vertices.size(), &vertices[0],
                   GL_DYNAMIC_DRAW);

  GLint numChars = 0;

  for(FFontHandler &it : fontHandler)
  {
    it.ready(this->uniformFontTexture);

    int size = it.getCharNum();

    GLint count = size / F_FONT_ENGINE_MAX_CHARACTERS_PER_DRAW + 
                    (size % F_FONT_ENGINE_MAX_CHARACTERS_PER_DRAW)?1:0;

    GLsizei* pCount = new GLsizei[count];
    const GLvoid** pIndices = new const GLvoid*[count];
    GLint* pBaseVertex = new GLint[count];

    int i = 0;

    for(; size > F_FONT_ENGINE_MAX_CHARACTERS_PER_DRAW; i++)
    {
      pCount[i] = F_FONT_ENGINE_MAX_CHARACTERS_PER_DRAW * 6;
      pBaseVertex[i] = numChars * 4;
      pIndices[i] = NULL;

      size -= F_FONT_ENGINE_MAX_CHARACTERS_PER_DRAW;
      numChars += F_FONT_ENGINE_MAX_CHARACTERS_PER_DRAW;
    }

    if(size > 0)
    {
      pCount[i] = size * 6;
      pBaseVertex[i] = numChars * 4;
      pIndices[i] = NULL;

      numChars += size;
    }

    glMultiDrawElementsBaseVertex(GL_TRIANGLES, pCount, GL_UNSIGNED_INT, 
                                  pIndices, count, pBaseVertex);

    delete[] pCount;
    delete[] pIndices;
    delete[] pBaseVertex;

    it.clearCharData();
  }
}
