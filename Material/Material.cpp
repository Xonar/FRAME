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
#include <assimp/types.h>

FMaterial::FMaterial(aiMaterial *material)
{
  material->Get(AI_MATKEY_COLOR_DIFFUSE, this->diffuse);
  material->Get(AI_MATKEY_COLOR_AMBIENT, this->ambient);
  material->Get(AI_MATKEY_COLOR_SPECULAR, this->specular);
  material->Get(AI_MATKEY_COLOR_EMISSIVE, this->emissive);
  material->Get(AI_MATKEY_SHININESS, this->shininess);

  //Get Texture
  
  //Diffuse
  if(material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
  {
    this->tDiffuse = new FTexture2D();
    aiString path;
    material->GetTexture(aiTextureType_DIFFUSE, 0, &path);
    this->tDiffuse->loadTextureFromFile(path.C_Str());
  }

  //Normals
  if(material->GetTextureCount(aiTextureType_NORMALS) > 0)
  {
    this->tNormal = new FTexture2D();
    aiString path;
    material->GetTexture(aiTextureType_NORMALS, 0, &path);
    this->tNormal->loadTextureFromFile(path.C_Str());
  }

  //Height Map
  if(material->GetTextureCount(aiTextureType_HEIGHT) > 0)
  {
    this->tHeight = new FTexture2D();
    aiString path;
    material->GetTexture(aiTextureType_HEIGHT, 0, &path);
    this->tHeight->loadTextureFromFile(path.C_Str());
  }
}

FMaterial::~FMaterial()
{
  //Nothing to do here
}

//Materials not yet implemented in shader and we can't bind to nothing
//FMaterial::bindMaterial(GLint index);

