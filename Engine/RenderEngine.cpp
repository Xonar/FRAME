/*
 * File :
 *      ./Engine/RenderEngine.cpp
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      Definitions of ./Engine/RenderEngine.h
 */

#include "RenderEngine.h"
#include "../Global.h"
#include "../Graphics/Graphics.h"
#include "../Lib/Log.h"

FRenderEngine::FRenderEngine()
{
  int width = gWindow->getWindowWidth();
  int height = gWindow->getWindowHeight();

  //Create FBOs
  glGenFramebuffers(1, &this->fbo_deferred);
  glGenFramebuffers(1, &this->fbo_final);

  //Create Textures
  glGenTextures(1, &this->t_deferred_col);
  glBindTexture(GL_TEXTURE_2D, this->t_deferred_col);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
  
  glGenTextures(1, &this->t_deferred_norm);
  glBindTexture(GL_TEXTURE_2D, this->t_deferred_norm);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

  glGenTextures(1, &this->t_deferred_pos);
  glBindTexture(GL_TEXTURE_2D, this->t_deferred_pos);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

  glGenTextures(1, &this->t_deferred_depth);
  glBindTexture(GL_TEXTURE_2D, this->t_deferred_depth);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);

  //Bind Textures to Framebuffer: fbo_deferred
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->fbo_deferred);
  glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 
                          this->t_deferred_col, 0);
  glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, 
                          this->t_deferred_norm, 0);
  glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, 
                          this->t_deferred_pos, 0);
  glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, 
                          this->t_deferred_depth, 0);

  GLenum drawBuffers[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
  glDrawBuffers(3, drawBuffers);

  //TODO Final Buffer

  //Load Shaders
  this->s_deferred = FShader();
  this->s_deferred.loadShader("Shader/FX/3D/3DCameraView.glvs", GL_VERTEX_SHADER);
  this->s_deferred.loadShader("Shader/FX/3D/3DCameraDeferred.glfs", GL_FRAGMENT_SHADER);
  this->s_deferred.loadProgram();

  this->s_world = FShader();
  this->s_world.loadShader("Shader/FX/3D/3DWorld.glvs", GL_VERTEX_SHADER);
  this->s_world.loadProgram();

  this->s_final = FShader();
  //this->s_final.loadShader("Shader/FX/3D/final.glfs" ,GL_FRAGMENT_SHADER);
  //this->s_final.loadProgram();

  //Get Uniform Locations from them
  this->u_deferred_wvs_matrix = glGetUniformLocation(s_deferred.getProgram(), "WorldViewScreenMatrix");
  this->u_deferred_mw_matrix = glGetUniformLocation(s_world.getProgram(), "ModelWorldMatrix");
  
}

void FRenderEngine::Init()
{
  //Set Uniform Block
}

void FRenderEngine::render()
{
  //Render to deferred textures
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->fbo_deferred);

  //Clear
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //Ignore ModelWorld step for now as model is in the same space as world

  //Set Shader
  s_deferred.bind();

  //Set Camera
  gCamera->use();
  gCamera->setMatrixUniform(u_deferred_wvs_matrix);

  //Set States
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  glDisable(GL_BLEND);

  //Draw
  gModelEngine->drawGeometry();

  //For Each Shadowing Light
  //TODO

  //TODO Compose scene

  //FIXME Currently drawing buffers to screen patches for testing
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
  glBindFramebuffer(GL_READ_FRAMEBUFFER, this->fbo_deferred);
  glReadBuffer(GL_COLOR_ATTACHMENT0);
  glBlitFramebuffer(0,0,640,480,320,240,640,480,GL_COLOR_BUFFER_BIT,GL_LINEAR);
  glReadBuffer(GL_COLOR_ATTACHMENT1);
  glBlitFramebuffer(0,0,640,480,0,0,320,240,GL_COLOR_BUFFER_BIT,GL_LINEAR);
  glReadBuffer(GL_COLOR_ATTACHMENT2);
  glBlitFramebuffer(0,0,640,480,320,0,640,240,GL_COLOR_BUFFER_BIT,GL_LINEAR);
}