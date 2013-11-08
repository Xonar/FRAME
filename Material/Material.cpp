/*
 * File :
 *      ./Material/Material.cpp
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      Definitions of ./Material/Material.cpp
 */

#include "Material.h"


FMaterial::FMaterial(aiMaterial *material)
{
  material->Get(AI_MATKEY_COLOR_DIFFUSE, this->diffuse);
  material->Get(AI_MATKEY_COLOR_AMBIENT, this->ambient);
  material->Get(AI_MATKEY_COLOR_SPECULAR, this->specular);
  material->Get(AI_MATKEY_COLOR_EMISSIVE, this->emissive);
  material->Get(AI_MATKEY_SHININESS, this->shininess);
}

FMaterial::~FMaterial()
{
  //Nothing to do here
}

//Materials not yet implemented in shader and we can't bind to nothing
//FMaterial::bindMaterial(GLint index);

