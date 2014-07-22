/*
 * File :
 *      ./Engine/LightEngine.h
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      DESCRIPTION
 */

#ifndef _F_H_LIGHTENGINE_
#define _F_H_LIGHTENGINE_

class FLightEngine;

#include <list>

#include "../Light/Light.h"
#include "../Shader/Shader.h"

class FLightEngine
{
  private:
    //Lights
    std::list<FLightDirectional*> lightsDirectional;

    //Shaders
    FShader s_directional; 

    //Uniforms
    //Directional Light
    GLint u_directional_d1_sampler;
    GLint u_directional_d2_sampler;
    GLint u_directional_d3_sampler;
    GLint u_directional_dir;
    GLint u_directional_dif;
    GLint u_directional_cpos;
    GLint u_directional_svw;

    //Point Light
    GLint u_point_d1_sampler;
    GLint u_point_d2_sampler;
    GLint u_point_d3_sampler;
    GLint u_point_pos;
    GLint u_point_dif;
    GLint u_point_cpos;
    GLint u_point_svw;

  public:
    FLightEngine();

    void registerLight(FLightDirectional* light);

    void render();
};

//Global Handle
extern FLightEngine *gLightEngine;

#endif // _F_H_LIGHTENGINE_
