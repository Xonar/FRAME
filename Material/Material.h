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

#include <glm/glm.hpp>
#include <assimp/material.h>

#include "../Graphics/Graphics.h"
#include "../Texture/Texture.h"

class FMaterial
{
  private:
    //Textures
    FTexture2D *tDiffuse;
    FTexture2D *tHeight;
    FTexture2D *tNormal;

    //Phong-Blinn Properties
    glm::vec3 diffuse;
    glm::vec3 ambient;
    glm::vec3 specular;
    glm::vec3 emissive;
    GLfloat shininess;
  public:
    FMaterial(aiMaterial *material);
    ~FMaterial();

    GLvoid bindMaterial(GLint index);
};

#endif //_F_H_MATERIAL_
