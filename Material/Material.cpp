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
#include "../Lib/Log.h"

FMaterial::FMaterial(aiMaterial *material)
{
  material->Get(AI_MATKEY_COLOR_SPECULAR, this->specular);
  material->Get(AI_MATKEY_SHININESS, this->shininess); //Exponenet

  //Get Texture

  //Diffuse
  if(material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
  {
    this->tDiffuse = new FTexture2D();
    aiString path;
    material->GetTexture(aiTextureType_DIFFUSE, 0, &path);
    this->tDiffuse->loadTextureFromFile("Assets/" + std::string(path.C_Str()));
  }
  else
  {
    gLogw << "Material Without Diffuse Texture!" << std::endl;
    this->tDiffuse = NULL;
  }

  //Normals
  if(material->GetTextureCount(aiTextureType_NORMALS) > 0)
  {
    this->tNormal = new FTexture2D();
    aiString path;
    material->GetTexture(aiTextureType_NORMALS, 0, &path);
    this->tNormal->loadTextureFromFile("Assets/" + std::string(path.C_Str()));
  }
  else
    this->tNormal = NULL;

  //Height Map
  if(material->GetTextureCount(aiTextureType_HEIGHT) > 0)
  {
    this->tHeight = new FTexture2D();
    aiString path;
    material->GetTexture(aiTextureType_HEIGHT, 0, &path);
    this->tHeight->loadTextureFromFile("Assets/" + std::string(path.C_Str()));
  }
  else
    this->tHeight = NULL;
}

FMaterial::~FMaterial()
{
  //Nothing to do here
}

//Materials not yet implemented in shader and we can't bind to nothing
void FMaterial::bindMaterial(GLint index)
{
  //Ignore Specular Components for now

  //Bind Textures to corrosponding units
  if(this->tDiffuse) tDiffuse->bindTexture(GL_TEXTURE0);
  if(this->tNormal) tNormal->bindTexture(GL_TEXTURE1);
  if(this->tHeight) tHeight->bindTexture(GL_TEXTURE2);
}

