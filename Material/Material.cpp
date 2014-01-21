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

FMaterial::FMaterial(aiMaterial *material, std::string directory)
{
  glm::vec3 tmpSpecular;
  material->Get(AI_MATKEY_COLOR_SPECULAR, tmpSpecular);
  material->Get(AI_MATKEY_SHININESS, this->shininess); //Exponenet
  this->specular = glm::length(tmpSpecular);

  //Get Texture

  //Diffuse
  if(material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
  {
    this->tDiffuse = new FTexture2D();
    aiString aiPath;
    material->GetTexture(aiTextureType_DIFFUSE, 0, &aiPath);
    std::string cPath(aiPath.C_Str());
    std::replace(cPath.begin(), cPath.end(), '\\', '/');
    this->tDiffuse->loadTextureFromFile(directory + cPath);
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
    aiString aiPath;
    material->GetTexture(aiTextureType_NORMALS, 0, &aiPath);
    std::string cPath(aiPath.C_Str());
    std::replace(cPath.begin(), cPath.end(), '\\', '/');
    this->tNormal->loadTextureFromFile(directory + cPath);
  }
  else
    this->tNormal = NULL;

  //Height Map
  if(material->GetTextureCount(aiTextureType_HEIGHT) > 0)
  {
    this->tHeight = new FTexture2D();
    aiString aiPath;
    material->GetTexture(aiTextureType_HEIGHT, 0, &aiPath);
    std::string cPath(aiPath.C_Str());
    std::replace(cPath.begin(), cPath.end(), '\\', '/');
    this->tHeight->loadTextureFromFile(directory + cPath);
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

