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
#include "Model/Model.h"
#include "Camera/Camera.h"
#include "Graphics/Graphics.h"
#include "Lib/FGLext.h"
#include "Container/Container.h"
#include "Time/Time.h"

#include <iostream>

//TODO Temp Resources
FModel *model;

FCamera *camera;

GLuint uniformViewScreenMatrix = 0;
GLuint uniformWorldViewMatrix = 0;
GLuint uniformOrthoMatrix = 0;
GLuint uniformFontSampler = 0;

FTexture2D *tex = NULL;
GLint uniformTextureSampler = 0;

FShader *shader = NULL;

FFont *font = NULL;

static const GLfloat g_uv_buffer_data[] = {
    0.000059f, 1.0f-0.000004f,
    0.000103f, 1.0f-0.336048f,
    0.335973f, 1.0f-0.335903f,
    1.000023f, 1.0f-0.000013f,
    0.667979f, 1.0f-0.335851f,
    0.999958f, 1.0f-0.336064f,
    0.667979f, 1.0f-0.335851f,
    0.336024f, 1.0f-0.671877f,
    0.667969f, 1.0f-0.671889f,
    1.000023f, 1.0f-0.000013f,
    0.668104f, 1.0f-0.000013f,
    0.667979f, 1.0f-0.335851f,
    0.000059f, 1.0f-0.000004f,
    0.335973f, 1.0f-0.335903f,
    0.336098f, 1.0f-0.000071f,
    0.667979f, 1.0f-0.335851f,
    0.335973f, 1.0f-0.335903f,
    0.336024f, 1.0f-0.671877f,
    1.000004f, 1.0f-0.671847f,
    0.999958f, 1.0f-0.336064f,
    0.667979f, 1.0f-0.335851f,
    0.668104f, 1.0f-0.000013f,
    0.335973f, 1.0f-0.335903f,
    0.667979f, 1.0f-0.335851f,
    0.335973f, 1.0f-0.335903f,
    0.668104f, 1.0f-0.000013f,
    0.336098f, 1.0f-0.000071f,
    0.000103f, 1.0f-0.336048f,
    0.000004f, 1.0f-0.671870f,
    0.336024f, 1.0f-0.671877f,
    0.000103f, 1.0f-0.336048f,
    0.336024f, 1.0f-0.671877f,
    0.335973f, 1.0f-0.335903f,
    0.667969f, 1.0f-0.671889f,
    1.000004f, 1.0f-0.671847f,
    0.667979f, 1.0f-0.335851f
};

//Vertex Data from http://www.opengl-tutorial.org/beginners-tutorials/tutorial-4-a-colored-cube/
static const GLfloat g_vertex_buffer_data[] = { 
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
     1.0f, 1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
     1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
     1.0f,-1.0f,-1.0f,
     1.0f, 1.0f,-1.0f,
     1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
     1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
     1.0f,-1.0f, 1.0f,
     1.0f, 1.0f, 1.0f,
     1.0f,-1.0f,-1.0f,
     1.0f, 1.0f,-1.0f,
     1.0f,-1.0f,-1.0f,
     1.0f, 1.0f, 1.0f,
     1.0f,-1.0f, 1.0f,
     1.0f, 1.0f, 1.0f,
     1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
     1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
     1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
     1.0f,-1.0f, 1.0f
};

GLint initializeGame()
{
  //Load Model
  model = new FModel();
 
  model->loadModelFromVertexAndTextureArray(g_vertex_buffer_data, g_uv_buffer_data, 36);

  //Create Shader
  shader = new FShader();

  shader->loadShader("Shader/FX/3D/3DForward.glvs",GL_VERTEX_SHADER);
  shader->loadShader("Shader/FX/3D/3DForward.glfs",GL_FRAGMENT_SHADER);

  shader->loadProgram();

  //Create Camera
  camera = new FCamera();

  camera->setViewPort(0,0,640,480);
  camera->setPosition(glm::vec3(4.f,3.f,-3.f));
  camera->lookAt(glm::vec3(0.f,0.f,0.f));
  camera->InitProjectionMatrix(45.f,0.1f,100.f);

  uniformViewScreenMatrix = glGetUniformLocation(shader->getProgram(), "ViewScreenMatrix" );
  uniformWorldViewMatrix = glGetUniformLocation(shader->getProgram(), "WorldViewMatrix" );

  //Set OpenGL Variables
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  //FFont
  font = new FFont();
  font->createFromTTF("Assets/TakaoPGothic.ttf", 18);

  gFontEngine->addFont(font);
  
  //Other
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  return 0;
}

GLvoid drawGame()
{
  static FTime start,end;
  FTime cur = FGetTime();

  //Bind Shader
  shader->bind();

  //Ready Model
  model->readyDraw();

  //Setup Ortho Matrix
  camera->setMatrixUniform(uniformWorldViewMatrix, uniformViewScreenMatrix);

  //Draw Model
  model->draw();

  //Draw FPS Counter - Measure between draws since VSync might be on
  font->drawText("time: " + FTimeString(end- start), glm::vec2(5,480 - 23) );
 
  //3.6 ms
  font->drawText("TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT", glm::vec2(10,10));
  font->drawText("TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT", glm::vec2(10,30));
  font->drawText("TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT", glm::vec2(10,50));
  font->drawText("TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT", glm::vec2(10,70));
  font->drawText("TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT", glm::vec2(10,90));
  font->drawText("TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT", glm::vec2(10,110));
  font->drawText("TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT", glm::vec2(10,130));
  font->drawText("TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT", glm::vec2(10,150));
  font->drawText("TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT", glm::vec2(10,170));
  font->drawText("TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT", glm::vec2(10,190));
  font->drawText("TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT", glm::vec2(10,210));
  font->drawText("TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT", glm::vec2(10,230));
  font->drawText("TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT", glm::vec2(10,250));
  font->drawText("TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT", glm::vec2(10,270));
  font->drawText("TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT", glm::vec2(10,290));
  font->drawText("TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT", glm::vec2(10,310));
  font->drawText("TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT", glm::vec2(10,330));
  font->drawText("TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT", glm::vec2(10,350));
  font->drawText("TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT", glm::vec2(10,370));
  font->drawText("TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT", glm::vec2(10,390));
  font->drawText("TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT", glm::vec2(10,410));
  font->drawText("TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT", glm::vec2(10,430));

  //font->drawText("Hello Font Engine!", glm::vec2(10,10));

  gFontEngine->render();

  end = FGetTime();
  start = cur;
}
