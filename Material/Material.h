/*
 * File :
 *      ./Material/Material.h
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      The FMaterial class stores the phong-blinn property of materials
 *        - Later this class will act as a base material and specific shading models will
 *          extend this base class
 */

#ifndef _F_H_MATERIAL_
#define _F_H_MATERIAL_

#include <SDL2/SDL_opengl.h>
#include <glm/glm.hpp>
#include <assimp/material.h>

class FMaterial
{
  private:
    //Phong-Blinn Properties
    glm::vec4 diffuse;
    glm::vec4 ambiant;
    glm::vec4 specular;
    glm::vec4 emissive;
    GLfloat shininess;
  public:
    FMaterial(aiMaterial material);
    ~FMaterial();

    bindMaterial(GLint index);
}

#endif //_F_H_MATERIAL_
