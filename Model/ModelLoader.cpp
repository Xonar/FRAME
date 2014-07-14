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
std::string FModelLoader::sceneDirectory;
float FModelLoader::sizeFactor = 1;

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
  return this->loadScene(path, 1);
}
const aiScene* FModelLoader::loadScene(const std::string &path, float sizeFactor)
{
  //Set Size Factor
  this->sizeFactor = sizeFactor;

  //Load Scene
  scene = aiImporter.ReadFile(path, 0
  | aiProcess_Triangulate
  | aiProcess_JoinIdenticalVertices
  | aiProcess_GenSmoothNormals
  | aiProcess_ValidateDataStructure 
  | aiProcess_FlipUVs
  | aiProcess_RemoveRedundantMaterials
    );

  if(!scene)
  {
    gLoge << "Failed loading scene : \"" << path << "\"" << std::endl;
  }

  this->sceneDirectory = path.substr(0, path.rfind("/") + 1);

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
      GLuint width = gWindow->getWindowWidth();
      GLuint height = gWindow->getWindowHeight();
      camera->setViewPort(0, 0, width, height);
      
      //Work out final Camera Node Transformation
      glm::mat4 mat = this->getNodeTransformation(cam->mName.C_Str());

      //Get Camera
      glm::vec3 pos = (mat * glm::vec4(aiGLM(cam->mPosition), 1.f)).xyz() * sizeFactor;
      glm::vec3 lookAt = (mat * glm::vec4(aiGLM(cam->mLookAt), 1.f)).xyz() * sizeFactor;
      glm::vec3 up = (mat * glm::vec4(aiGLM(cam->mUp),0.f)).xyz();
      float cpnear = cam->mClipPlaneNear;
      float cpfar = cam->mClipPlaneFar;
      //Convert from Horizontal Radians to Vertical Radians
      float fov = glm::radians(cam->mHorizontalFOV * 57.2957795 / width * height);

      //Set Camera Attributes
      camera->setPosition(pos);
      camera->setUp(up);
      camera->lookAt(lookAt);
      camera->InitProjectionMatrix(fov, cpnear, cpfar);

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

FModel* FModelLoader::getMesh(const GLuint i, const aiScene *s)
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

      //Node Transformation
      aiNode* meshNode = this->getCorrospondingNode(i, s->mRootNode);
      glm::mat4 nodeTransform = this->getNodeTransformation(meshNode, s->mRootNode);

      //Populate Vertices

      //Positions
      if(mesh->HasPositions())
        for(GLuint i = 0;i < numVertices; i++)
          vertices[i].pos = (nodeTransform * glm::vec4(aiGLM(mesh->mVertices[i]),1.f)).xyz() * sizeFactor;
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

      //Populate Indices
      for(GLuint i = 0;i < mesh->mNumFaces; i++)
      {
        indices[i*3 + 0] = mesh->mFaces[i].mIndices[0];
        indices[i*3 + 1] = mesh->mFaces[i].mIndices[1];
        indices[i*3 + 2] = mesh->mFaces[i].mIndices[2];
  
      }

      //Create Model Part
      part->loadModelPartFromVerticesAndIndices(vertices, numVertices, indices, numIndices);

      //Create Model from part and material
      FModel *model = new FModel();
      model->createModelFromPartsAndMaterial(&part, 1, mesh->mMaterialIndex);

      //Free Memory
      delete[] vertices;
      delete[] indices;

      return model;
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

FMaterial* FModelLoader::getMaterial(const GLuint i, const aiScene *s)
{
  if(s != NULL)
  {
    if(s->mNumMaterials > i)
    {
      return new FMaterial(s->mMaterials[i], this->sceneDirectory);
    }
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
  const aiNode* child = root->FindNode(name.c_str());
  
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

glm::mat4 FModelLoader::getNodeTransformation(aiNode *leaf, aiNode *root)
{
  //Start with identity matrix
  glm::mat4 transform = glm::mat4();

  //Iterate upwards to get final matrix
  while(leaf->mName != root->mName)
  {
    transform = aiGLM(leaf->mTransformation) * transform;
    leaf = leaf->mParent;
  }

  //Return Tranformation Matrix
  return transform;
}

aiNode* FModelLoader::getCorrospondingNode(const unsigned int mesh, aiNode *root)
{
  //DFS to find corrosponding node
  //TODO create lookup structure when loading scene for faster searching
  
  //Check if mesh is in current node
  for(GLuint i = 0; i < root->mNumMeshes; i++)
    if(mesh == root->mMeshes[i])
      return root;

  //Search children nodes
  for(GLuint i = 0; i < root->mNumChildren; i++)
  {
    aiNode* ret = getCorrospondingNode(mesh, root->mChildren[i]);
    if(ret)
      return ret;
  }

  return NULL;
}
