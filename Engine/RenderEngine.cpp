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
#include "../Camera/Camera.h"
#include "../Graphics/Graphics.h"
#include "../Lib/Log.h"
#include "../Lib/FGLext.h"
#include "../Shader/ShaderManager.h"
#include "../Window/Window.h"
#include "../Engine/LightEngine.h"
#include "../Engine/ModelEngine.h"

void FRenderEngine::createGBufferTexture(GLuint &tex, GLenum format, GLint width, GLint height)
{
  glGenTextures(1, &tex);
  glBindTexture(GL_TEXTURE_2D, tex);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);
}

FRenderEngine::FRenderEngine()
{
  int width = gWindow->getWindowWidth();
  int height = gWindow->getWindowHeight();

  //Create FBOs
  glGenFramebuffers(1, &this->fbo_deferred);
  glGenFramebuffers(1, &this->fbo_light);
  glGenFramebuffers(1, &this->fbo_pos);

  //Create Textures
  gLogv << "Creating Gbuffer: Color" << std::endl;
  createGBufferTexture(this->t_deferred_col, GL_RGBA8, width, height);
  
  gLogv << "Creating Gbuffer: Normals" << std::endl;
  //createGBufferTexture( this->t_deferred_norm, GL_RGBA8_SNORM, width,height);
  createGBufferTexture( this->t_deferred_norm, GL_RGBA8, width,height);

  gLogv << "Creating Gbuffer: Depth" << std::endl;
  createGBufferTexture( this->t_deferred_depth, GL_DEPTH_COMPONENT24, width,height);

  gLogv << "Creating Gbuffer: Light" << std::endl;
  createGBufferTexture( this->t_deferred_light, GL_RGBA16F, width,height);

  gLogv << "Creating Gbuffer: Position" << std::endl;
  createGBufferTexture( this->t_deferred_pos, GL_RGBA16F, width,height);

  //Bind Textures to Framebuffer: fbo_deferred
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->fbo_deferred);
  glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 
                          this->t_deferred_col, 0);
  glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, 
                          this->t_deferred_norm, 0);
  glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, 
                          this->t_deferred_depth, 0);

  //Set Buffer to draw
  const GLenum drawBuffers[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
  glDrawBuffers(2, drawBuffers);

  //Check Framebuffer status
  GLenum fbo_status = glCheckFramebufferStatus( GL_DRAW_FRAMEBUFFER );

  if(fbo_status != GL_FRAMEBUFFER_COMPLETE)
    gLogw << "Framebuffer status (GBuffer):" << glFramebufferCompleteString(fbo_status) << std::endl;

  //Bind Texture to Framebuffer: fbo_light
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->fbo_light);
  glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                          this->t_deferred_light, 0);

  //Set Buffer to draw
  glDrawBuffers(1, drawBuffers);

  //Check Framebuffer status
  fbo_status = glCheckFramebufferStatus( GL_DRAW_FRAMEBUFFER );

  if(fbo_status != GL_FRAMEBUFFER_COMPLETE)
    gLogw << "Framebuffer status (Light): " << glFramebufferCompleteString(fbo_status) << std::endl;

  //Bind Textures to Framebuffer: fbo_pos
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->fbo_pos);
  glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                          this->t_deferred_pos, 0);

  //Set Buffer to draw
  glDrawBuffers(1, drawBuffers);

  //Check Framebuffer status
  fbo_status = glCheckFramebufferStatus( GL_DRAW_FRAMEBUFFER );

  if(fbo_status != GL_FRAMEBUFFER_COMPLETE)
    gLogw << "Framebuffer status (Position): " << glFramebufferCompleteString(fbo_status) << std::endl;

  //Load Shaders
  this->s_deferred = *gShaderManager->loadShader("3DCameraDeferred",
      "Shader/FX/3D/3DCameraView.glvs", "Shader/FX/3D/3DCameraDeferred.glfs");

  this->s_compose = *gShaderManager->loadShader("3DCompose", "Shader/FX/3D/3DCompose.glvs",
      "Shader/FX/3D/3DCompose.glfs");

  this->s_pos = *gShaderManager->loadShader("3DPositionDeferred", "Shader/FX/3D/3DCompose.glvs",
      "Shader/FX/3D/3DPositionDeferred.glfs");

  //Get Uniform Locations from them
  this->u_deferred_texture_sampler = glGetUniformLocation(s_deferred.getProgram(), "tTexture");
  this->u_deferred_normal_sampler = glGetUniformLocation(s_deferred.getProgram(), "tNormal");
  this->u_deferred_height_sampler = glGetUniformLocation(s_deferred.getProgram(), "tHeight");
  this->u_deferred_wvs_matrix = glGetUniformLocation(s_deferred.getProgram(), "WorldViewScreenMatrix");

  this->u_compose_deferred_1_sampler = glGetUniformLocation(s_compose.getProgram(), "tDeferred1");
  this->u_compose_deferred_2_sampler = glGetUniformLocation(s_compose.getProgram(), "tDeferred2");
  this->u_compose_deferred_3_sampler = glGetUniformLocation(s_compose.getProgram(), "tDeferred3");
  this->u_compose_light_sampler = glGetUniformLocation(s_compose.getProgram(), "tLight");

  this->u_pos_depth_sampler = glGetUniformLocation(s_pos.getProgram(), "tDepth");
  this->u_pos_cam_pos_vec = glGetUniformLocation(s_pos.getProgram(), "uCamPos");
  this->u_pos_svw = glGetUniformLocation(s_pos.getProgram(), "ScreenViewWorldMatrix");

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

  s_pos.bind();
  glUniform1i(u_pos_depth_sampler, 4);

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
  glActiveTexture(GL_TEXTURE4);
  glBindTexture(GL_TEXTURE_2D, t_deferred_depth);

  //Bind screen quad VAO
  glBindVertexArray(this->vao);

  //Create Position G-Buffer

  //Bind Shader
  s_pos.bind();

  //Set Position FBO
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->fbo_pos);
  //glClear - no clear necesarry as everything is drawn over

  //Set Camera Uniforms
  gCamera->setPositionUniform(this->u_pos_cam_pos_vec);
  gCamera->setInverseMatrixUniform(this->u_pos_svw);

  //Draw Position GBuffer
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, NULL);

  //Lights

  //Set Light FBO
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->fbo_light);
  glClear(GL_COLOR_BUFFER_BIT);

  //Bind Position GBuffer
  glActiveTexture(GL_TEXTURE3);
  glBindTexture(GL_TEXTURE_2D, t_deferred_pos);

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
