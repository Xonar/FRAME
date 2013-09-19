/*
 * File :
 *      ./Game.cpp
 *
 * Author : 
 *      Xonar <Paul le Roux>
 *
 * Description :
 *      Definitions of ./Game.h
 *
 */

#include "Game.h"
#include "Global.h"
#include "Texture/Texture.h"
#include "Camera/Camera.h"
#include "Graphics/Graphics.h"
#include "Lib/FGLext.h"

#include <iostream>

//TODO Temp Resources

FShader *shader = NULL;

const GLfloat Triangle_Vertex_Buffer_Data[] = {
  -1.0f, -1.0f,
   1.0f, -1.0f,
   0.0f,  1.0f,
};

GLuint triangleVertexArray = 0;
GLuint triangleVertexBuffer = 0;

GLint initializeGame()
{
  //Create Shader
  shader = new FShader();

  shader->loadShader("Shader/FX/2D/2d.glvs",GL_VERTEX_SHADER);
  shader->loadShader("Shader/FX/2D/2d.glfs",GL_FRAGMENT_SHADER);

  shader->loadProgram();

  //Create Vertex Array
  glGenVertexArrays(1, &triangleVertexArray);
  glBindVertexArray(triangleVertexArray);

  //Create Vertex Buffer
  glGenBuffers(1, &triangleVertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, triangleVertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle_Vertex_Buffer_Data), Triangle_Vertex_Buffer_Data, GL_STATIC_DRAW);

  return 0;
}

GLvoid drawGame()
{
  shader->bind();

  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, triangleVertexBuffer);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*) 0);

  glDrawArrays(GL_TRIANGLES, 0, 3);

  glDisableVertexAttribArray(0);
}
