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
#include "../Global.h"

#include <assimp/postprocess.h>

//Define FModelLoader static variables
Assimp::Importer FModelLoader::aiImporter;
const aiScene* FModelLoader::scene;
const aiMesh* FModelLoader::mesh;

glm::vec3 aiGLM(aiColor3D col)
{
  return glm::vec3(col.r, col.g, col.b);
}

FModelLoader::FModelLoader()
{
  scene = NULL;
  mesh = NULL;
}

FModelLoader::~FModelLoader()
{
  scene = NULL;
  mesh = NULL;
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

GLuint FModelLoader::getCameraCount(const aiScene* s)
{
  if(s != NULL)
    return s->mNumCameras;
  else
  {
    gLogw << "No active scene!" << std::endl;
    return 0;
  }
}

FCamera* FModelLoader::getCamera(const GLuint i,const aiScene* s)
{
  if(s != NULL)
  {
    if(s->mNumCameras > i)
    {
      const aiCamera* cam = s->mCameras[i];
      FCamera *camera = new FCamera;

      //Set with default viewport
      camera->setViewPort(0,0,gWindow->getWindowWidth(),gWindow->getWindowHeight());
      
      //Get Camera Matrix
      aiMatrix4x4 aiMat;
      cam->GetCameraMatrix(aiMat);

      //Work out final Camera Node Transformation
      glm::mat4 nodeTransform = this->getNodeTransformation(cam->mName.C_Str());
      glm::mat4 mat = nodeTransform * aiGLM(aiMat);

      //Get Camera
      glm::vec3 pos = (mat * glm::vec4(aiGLM(cam->mPosition), 1.f)).xyz();
      glm::vec3 lookAt = (mat * glm::vec4(aiGLM(cam->mLookAt), 1.f)).xyz();
      //glm::vec3 up = aiGLM(cam->mUp); - UNUSED BY CAMERA
      float cpnear = cam->mClipPlaneNear;
      float cpfar = cam->mClipPlaneFar;
      float fov = cam->mHorizontalFOV;

      //Set Camera Attributes
      camera->setPosition(pos);
      camera->lookAt(lookAt);
      camera->InitProjectionMatrix(fov*180/M_PI, cpnear, cpfar);

      return camera;
    }
    else
    {
      gLogw << "Camera at index " << i << " doesn\'t exist" << std::endl;
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

FModelPart* FModelLoader::getMesh(const GLuint i, const aiScene *s)
{
  if(s != NULL)
  {
    if(s->mNumMeshes > i)
    {
      const aiMesh* mesh = s->mMeshes[i];
      FModelPart* part = new FModelPart();
      GLuint numIndices = mesh->mNumFaces * 3;
      GLuint* indices = new GLuint[numIndices];
      GLuint numVertices = mesh->mNumVertices;
      FVertex3* vertices = new FVertex3[numVertices];

      //Populate Vertices

      //Positions
      if(mesh->HasPositions())
        for(GLuint i = 0;i < numVertices; i++)
          vertices[i].pos = aiGLM(mesh->mVertices[i]);
      else
      {
        gLogw << "Mesh Doesn't Contain Positions! Can't create Part." << std::endl;
        delete[] vertices;
        delete[] indices;
        return NULL;
      }

      //Normals
      if(mesh->HasNormals())
        for(GLuint i = 0; i < numVertices; i++)
          vertices[i].nor = aiGLM(mesh->mNormals[i]);
      
      //UV
      if(mesh->HasTextureCoords(0))
        for(GLuint i = 0;i < numVertices; i++)
          vertices[i].tex = aiGLM(mesh->mTextureCoords[0][i]).xy();

      //Create Model Part
      part->loadModelPartFromVerticesAndIndices(vertices, numVertices, indices, numIndices);

      //Free Memory
      delete[] vertices;
      delete[] indices;

      return part;
    }
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

glm::mat4 FModelLoader::getNodeTransformation(const std::string& name, aiNode *root)
{
  aiString aiName = aiString(name);
  const aiNode* child = root->FindNode(aiName);
  
  //Start with identity matrix
  glm::mat4 transform = glm::mat4();

  //Iterate upwards to get final matrix
  while(child->mName != root->mName)
  {
    transform = aiGLM(child->mTransformation) * transform;
    child = child->mParent;
  }

  //Return Tranformation Matrix
  return transform;
}
