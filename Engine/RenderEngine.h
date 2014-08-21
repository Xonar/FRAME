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

class FRenderEngine;

#include "../Graphics/Graphics.h"
#include "../Shader/Shader.h"

class FRenderEngine
{
 private:
  //FBO's
  GLuint fbo_deferred;
  GLuint fbo_light;
  GLuint fbo_pos;

  //Textures
  GLuint t_deferred_col;
  GLuint t_deferred_norm;
  GLuint t_deferred_depth;
  GLuint t_deferred_light;
  GLuint t_deferred_pos;

  //Shaders
  FShader s_deferred;
  FShader s_compose;
  FShader s_pos;

  //Uniforms
  GLuint u_deferred_wvs_matrix;
  GLuint u_deferred_mw_matrix;
  GLuint u_deferred_texture_sampler;
  GLuint u_deferred_normal_sampler;
  GLuint u_deferred_height_sampler;

  GLuint u_compose_deferred_1_sampler;
  GLuint u_compose_deferred_2_sampler;
  GLuint u_compose_deferred_3_sampler;
  GLuint u_compose_light_sampler;

  GLuint u_pos_depth_sampler;
  GLuint u_pos_cam_pos_vec;
  GLuint u_pos_svw;

  //Deferred Qua
  GLuint vao;
  GLuint vbo;
  GLuint ibo;

  //Private Functions used to reduce code size
  void createGBufferTexture(GLuint &tex, GLenum format, GLint width, GLint height);

 public:
  FRenderEngine();
  void Init();

  void render();
};

//Global Handle
extern FRenderEngine *gRenderEngine;

#endif //_F_H_RENDER_ENGINE_
