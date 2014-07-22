/*
 * File :
 *      ./Engine/LightEngine.cpp
 *
 * Author : 
 *      Xonar <Paul le Roux>
 *
 * Description :
 *      Definitions of ./Engine/LightEngine.h
 *      
 */
 
#include "LightEngine.h"
#include "../Camera/Camera.h"
#include "../Shader/ShaderManager.h"

FLightEngine::FLightEngine()
{
  //Load Shaders
  this->s_directional = *gShaderManager->loadShader("LightDirectional",
      "Shader/FX/3D/3DCompose.glvs", "Shader/FX/Light/LightDirectional.glfs");

  //Get Uniforms
  this->u_directional_d1_sampler = glGetUniformLocation(s_directional.getProgram(), "tDeferred1");
  this->u_directional_d2_sampler = glGetUniformLocation(s_directional.getProgram(), "tDeferred2");
  this->u_directional_dir = glGetUniformLocation(s_directional.getProgram(), "uDirection");
  this->u_directional_dif = glGetUniformLocation(s_directional.getProgram(), "uDiffuse");
  this->u_directional_cpos = glGetUniformLocation(s_directional.getProgram(), "uCamPos");
  this->u_directional_svw = glGetUniformLocation(s_directional.getProgram(), "ScreenViewWorldMatrix");

  //Bind Uniforms
  this->s_directional.bind();
  glUniform1i(u_directional_d1_sampler, 0);
  glUniform1i(u_directional_d2_sampler, 1);
}

void FLightEngine::registerLight(FLightDirectional* light)
{
  this->lightsDirectional.push_back(light);
}

void FLightEngine::render()
{
  //Directional Lights
  this->s_directional.bind();

  //Set Uniforms
  gCamera->setInverseMatrixUniform(this->u_directional_svw);

  //Loop over directional lights
  for(FLightDirectional* l : lightsDirectional)
  {
    //Set Uniforms
    glUniform3fv(this->u_directional_dir, 1, &l->getDirection()[0]);
    glUniform3fv(this->u_directional_dif, 1, &l->getDiffuse()[0]);

    //Draw Light
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, NULL);
  }
}
