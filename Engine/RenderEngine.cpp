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
#include "../Lib/FGLext.h"

FRenderEngine::FRenderEngine()
{
  int width = gWindow->getWindowWidth();
  int height = gWindow->getWindowHeight();

  //Create FBOs
  glGenFramebuffers(1, &this->fbo_deferred);
  glGenFramebuffers(1, &this->fbo_light);

  //Create Textures
  glGenTextures(1, &this->t_deferred_col);
  glBindTexture(GL_TEXTURE_2D, this->t_deferred_col);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  
  glGenTextures(1, &this->t_deferred_norm);
  glBindTexture(GL_TEXTURE_2D, this->t_deferred_norm);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glGenTextures(1, &this->t_deferred_pos);
  glBindTexture(GL_TEXTURE_2D, this->t_deferred_pos);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glGenTextures(1, &this->t_deferred_depth);
  glBindTexture(GL_TEXTURE_2D, this->t_deferred_depth);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glGenTextures(1, &this->t_deferred_light);
  glBindTexture(GL_TEXTURE_2D, this->t_deferred_light);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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

  //Set Buffer to draw
  const GLenum drawBuffers[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
  glDrawBuffers(3, drawBuffers);

  //Bind Texture to Framebuffer: fbo_light
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->fbo_light);
  glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                          this->t_deferred_light, 0);

  //Set Buffer to draw
  glDrawBuffers(1, drawBuffers);

  //Load Shaders
  this->s_deferred = FShader();
  this->s_deferred.loadShader("Shader/FX/3D/3DCameraView.glvs", GL_VERTEX_SHADER);
  this->s_deferred.loadShader("Shader/FX/3D/3DCameraDeferred.glfs", GL_FRAGMENT_SHADER);
  this->s_deferred.loadProgram();

  this->s_compose = FShader();
  this->s_compose.loadShader("Shader/FX/3D/3DCompose.glvs", GL_VERTEX_SHADER);
  this->s_compose.loadShader("Shader/FX/3D/3DCompose.glfs", GL_FRAGMENT_SHADER);
  this->s_compose.loadProgram();

  //Get Uniform Locations from them
  this->u_deferred_texture_sampler = glGetUniformLocation(s_deferred.getProgram(), "tTexture");
  this->u_deferred_normal_sampler = glGetUniformLocation(s_deferred.getProgram(), "tNormal");
  this->u_deferred_height_sampler = glGetUniformLocation(s_deferred.getProgram(), "tHeight");
  this->u_deferred_wvs_matrix = glGetUniformLocation(s_deferred.getProgram(), "WorldViewScreenMatrix");

  this->u_compose_deferred_1_sampler = glGetUniformLocation(s_compose.getProgram(), "tDeferred1");
  this->u_compose_deferred_2_sampler = glGetUniformLocation(s_compose.getProgram(), "tDeferred2");
  this->u_compose_deferred_3_sampler = glGetUniformLocation(s_compose.getProgram(), "tDeferred3");
  this->u_compose_light_sampler = glGetUniformLocation(s_compose.getProgram(), "tLight");

  //Bind Samplers to texture units
  s_deferred.bind();
  glUniform1i(u_deferred_texture_sampler, 0);
  glUniform1i(u_deferred_normal_sampler, 1);
  glUniform1i(u_deferred_height_sampler, 2);

  s_compose.bind();
  glUniform1i(u_compose_deferred_1_sampler, 0);
  glUniform1i(u_compose_deferred_2_sampler, 1);
  glUniform1i(u_compose_deferred_3_sampler, 2);
  glUniform1i(u_compose_light_sampler, 3);

  //Create Quad for Deferred pass
  glGenBuffers(1, &this->ibo);
  glGenBuffers(1, &this->vbo);
  glGenVertexArrays(1, &this->vao);

  //Buffer Data
  GLubyte ib[] = {0,1,2,0,2,3};
  FVertexDeferred vb[] = {glm::vec2(0.f,0.f), glm::vec2(0.f,1.f), 
                          glm::vec2(1.f,1.f), glm::vec2(1.f,0.f)};

  //Bind Buffers
  glBindVertexArray(this->vao);
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);

  //Upload Data
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 6, ib, GL_STATIC_DRAW);
  glBufferData(GL_ARRAY_BUFFER, sizeof(FVertexDeferred) * 4, vb, GL_STATIC_DRAW);

  //Set Vertex Attributes
  glEnableVertexAttribs(F_VERTEX_DEFERRED);
  glVertexAttribPointers(F_VERTEX_DEFERRED);
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

  //glEnable(GL_CULL_FACE);
  //glCullFace(GL_BACK);
  
  glDisable(GL_CULL_FACE);

  glDisable(GL_BLEND);

  //Draw
  gModelEngine->drawTextured();

  //Ready
  glDepthMask(GL_FALSE);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);

  //Compose scene

  //Bind Textures
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, t_deferred_col);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, t_deferred_norm);
  glActiveTexture(GL_TEXTURE2);
  glBindTexture(GL_TEXTURE_2D, t_deferred_pos);

  //Bind screen quad VAO
  glBindVertexArray(this->vao);

  //Lights

  //Set Light FBO
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->fbo_light);
  glClear(GL_COLOR_BUFFER_BIT);

  //Set Required Blending
  glEnable(GL_BLEND);
  glBlendEquation(GL_FUNC_ADD);
  glBlendFunc(GL_ONE, GL_ONE);

  //Render Lights
  gLightEngine->render();  

  //Use Screen FBO
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

  //Bind Light Texture
  glActiveTexture(GL_TEXTURE3);
  glBindTexture(GL_TEXTURE_2D, t_deferred_light);

  //Turn of blending
  glDisable(GL_BLEND);

  //Ready by Binding Shader
  s_compose.bind();

  //Fire
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, NULL);

  //Reset state
  glDepthMask(GL_TRUE);
}
