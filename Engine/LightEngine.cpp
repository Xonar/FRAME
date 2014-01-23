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
#include "../Global.h"

FLightEngine::FLightEngine()
{
  //Load Shaders
  this->s_directional = FShader();
  this->s_directional.loadShader("Shader/FX/3D/3DCompose.glvs", GL_VERTEX_SHADER);
  this->s_directional.loadShader("Shader/FX/Light/LightDirectional.glfs", GL_FRAGMENT_SHADER);
  this->s_directional.loadProgram();

  //Get Uniforms
  this->u_directional_d1_sampler = glGetUniformLocation(s_directional.getProgram(), "tDeferred1");
  this->u_directional_d2_sampler = glGetUniformLocation(s_directional.getProgram(), "tDeferred2");
  this->u_directional_d3_sampler = glGetUniformLocation(s_directional.getProgram(), "tDeferred3");
  this->u_directional_dir = glGetUniformLocation(s_directional.getProgram(), "uDirection");
  this->u_directional_dif = glGetUniformLocation(s_directional.getProgram(), "uDiffuse");
  this->u_directional_cpos = glGetUniformLocation(s_directional.getProgram(), "uCamPos");

  //Bind Uniforms
  this->s_directional.bind();
  glUniform1i(u_directional_d1_sampler, 0);
  glUniform1i(u_directional_d2_sampler, 1);
  glUniform1i(u_directional_d3_sampler, 2);
}

void FLightEngine::registerLight(FLightDirectional* light)
{
  this->lightsDirectional.push_back(light);
}

void FLightEngine::render()
{
  //Directional Lights
  this->s_directional.bind();
  glUniform3fv(this->u_directional_cpos, 1, &gCamera->getPosition()[0]);
  for(FLightDirectional* l : lightsDirectional)
  {
    //Set Uniforms
    glUniform3fv(this->u_directional_dir, 1, &l->getDirection()[0]);
    glUniform3fv(this->u_directional_dif, 1, &l->getDiffuse()[0]);

    //Draw Light
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, NULL);
  }
}
