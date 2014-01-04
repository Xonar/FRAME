/*
 * File :
 *      ./Engine/RenderEngine.h
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      This is the super structure that composes the 3D scene.
 */

#ifndef _F_H_RENDER_ENGINE_
#define _F_H_RENDER_ENGINE_

#include "ModelEngine.h"
#include "../Graphics/Graphics.h"
#include "../Shader/Shader.h"

class FRenderEngine
{
 private:
  //FBO's
  GLuint fbo_deferred;

  //Textures
  GLuint t_deferred_col;
  GLuint t_deferred_norm;
  GLuint t_deferred_pos;
  GLuint t_deferred_depth;

  //Shaders
  FShader s_deferred;
  FShader s_compose;

  //Uniforms
  GLuint u_deferred_wvs_matrix;
  GLuint u_deferred_mw_matrix;
  GLuint u_deferred_texture_sampler;
  GLuint u_deferred_normal_sampler;
  GLuint u_deferred_height_sampler;
  GLuint u_compose_diffuse_sampler;
  GLuint u_compose_normal_sampler;
  GLuint u_compose_depth_sampler;

  //Deferred Qua
  GLuint vao;
  GLuint vbo;
  GLuint ibo;

 public:
  FRenderEngine();
  void Init();

  void render();
};

#endif //_F_H_RENDER_ENGINE_
