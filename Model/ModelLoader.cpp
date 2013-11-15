/*
 * File :
 *      ./Model/ModelLoader.cpp
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      Definitions of ./Model/ModelLoader.h
 */

#include "ModelLoader.h"
#include "../Lib/Log.h"

#include <glm/gtc/type_ptr.hpp>
#include <assimp/postprocess.h>

//Define FModelLoader static variables
Assimp::Importer FModelLoader::aiImporter;
const aiScene* FModelLoader::scene;
const aiMesh* FModelLoader::mesh;

glm::vec3 aiGLM(aiColor3D col)
{
  return glm::vec3(col.r, col.g, col.b);
}

template <typename T> glm::vec2 aiGLM(aiVector2t<T> vec)
{
  return glm::vec2(vec.x, vec.y);
}

template <typename T> glm::vec3 aiGLM(aiVector3t<T> vec)
{
  return glm::vec3(vec.x, vec.y, vec.z);
}

template <typename T> glm::vec4 aiGLM(aiColor4t<T> col)
{
  return glm::vec4(col.r, col.g, col.b, col.a);
}

template <typename T> glm::mat3 aiGLM(aiMatrix3x3t<T> mat)
{
  return glm::make_mat3(&mat).transpose();
}

template <typename T> glm::mat4 aiGLM(aiMatrix4x4t<T> mat)
{
  return glm::make_mat4(&mat).transpose();
}


FModelLoader::FModelLoader()
{
  scene = NULL;
  mesh = NULL;
}

FModelLoader::~FModelLoader()
{
  //TODO
}
    
const aiScene* FModelLoader::loadScene(const std::string &path)
{
  //Load Scene
  scene = aiImporter.ReadFile(path, 0
  | aiProcess_Triangulate
  | aiProcess_JoinIdenticalVertices
  | aiProcess_GenSmoothNormals
  | aiProcess_ValidateDataStructure 
    );

  if(!scene)
  {
    gLoge << "Failed loading scene : \"" << path << "\"" << std::endl;
  }

  return scene;
}

GLuint FModelLoader::getAnimationCount(const aiScene* s)
{
  if(s != NULL)
    return s->mNumAnimations;
  else
  {
    gLogw << "No active scene!" << std::endl;
    return 0;
  }
}

const aiAnimation* FModelLoader::getAnimation(const GLuint i,const aiScene* s)
{
  if(s != NULL)
  {
    if(s->mNumAnimations > i)
      return s->mAnimations[i];
    else
    {
      gLogw << "Animation at index " << i << " doesn\'t exist" << std::endl;
      return NULL;
    }
  }
  else
  {
    gLogw << "No active scene!" << std::endl;
    return NULL;
  }
}


GLuint FModelLoader::getMeshCount(const aiScene *s)
{
  if(s != NULL)
    return s->mNumMeshes;
  else
  {
    gLogw << "No active scene!" << std::endl;
    return 0;
  }
}

const aiMesh* FModelLoader::getMeshCount(const GLuint i, const aiScene *s)
{
  if(s != NULL)
  {
    if(s->mNumMeshes > i)
      return s->mMeshes[i];
    else
    {
      gLogw << "Mesh at index " << i << " doesn\'t exist" << std::endl;
      return NULL;
    }
  }
  else
  {
    std::cerr << "No active scene!" << std::endl;
    return NULL;
  }
}

GLuint FModelLoader::getBoneCount(const aiMesh *m)
{
  if(m != NULL)
    return m->mNumBones;
  else
  {
    gLogw << "No active scene!" << std::endl;
    return 0;
  }
}

const aiBone* FModelLoader::getBone(const GLuint i, const aiMesh *m)
{
  if(m != NULL)
  {
    if(m->mNumBones > i)
      return m->mBones[i];
    else
    {
      gLogw << "Bone at index " << i << " doesn\'t exist" << std::endl;
      return NULL;
    }
  }
  else
  {
    gLogw << "No active scene!" << std::endl;
    return NULL;
  }
}

GLuint FModelLoader::getMaterialCount(const aiScene *s)
{
  if(s != NULL)
    return s->mNumMaterials;
  else
  {
    gLogw << "No active scene!" << std::endl;
    return 0;
  }
}

const aiMaterial* FModelLoader::getMaterial(const GLuint i, const aiScene *s)
{
  if(s != NULL)
  {
    if(s->mNumMaterials > i)
      return s->mMaterials[i];
    else
    {
      gLogw << "Material at index " << i << " doesn\'t exist" << std::endl;
      return NULL;
    }
  }
  else
  {
    gLogw << "No active scene!" << std::endl;
    return NULL;
  }
}
