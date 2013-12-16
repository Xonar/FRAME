/*
 * File :
 *      ./Model/ModelLoader.h
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      The FModelLoader handles the loading of models (What did you expect?)
 */

#ifndef _F_H_MODEL_LOADER_
#define _F_H_MODEL_LOADER_

#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/anim.h>
#include <assimp/material.h>
#include <assimp/Importer.hpp>

#define GLM_SWIZZLE
#include <glm/glm.hpp>

#include "../Graphics/Graphics.h"
#include "../Camera/Camera.h"
#include "../Model/ModelPart.h"

//Functions that convert between assimp classes and glm structs
glm::vec3 aiGLM(aiColor3D col);
#include "ModelLoader.template.h"

class FModelLoader
{
  private:
    //Import
    static Assimp::Importer aiImporter;

    //Cached variables for easier access
    static const aiScene* scene;
    static const aiMesh* mesh;

  public:
    //Constructor/Deconstructor
    FModelLoader();
    ~FModelLoader();
    
    //Loads Scene and caches scene
    const aiScene* loadScene(const std::string &path);

    //Get Animation[Count]
    GLuint getAnimationCount(const aiScene *s = scene);
    const aiAnimation* getAnimation(const GLuint i,const aiScene *s = scene);

    //Get Camera[Count]
    GLuint getCameraCount(const aiScene *s = scene);
    FCamera* getCamera(const GLuint i, const aiScene *s = scene);

    //Get Mesh[Count]
    GLuint getMeshCount(const aiScene *s = scene);
    FModelPart* getMesh(const GLuint i, const aiScene *s = scene);

    //Get Bone[Count]
    GLuint getBoneCount(const aiMesh *m = mesh);
    const aiBone* getBone(const GLuint i, const aiMesh *m = mesh);

    //Get Material[Count]
    GLuint getMaterialCount(const aiScene *s = scene);
    const aiMaterial* getMaterial(const GLuint i, const aiScene *s = scene);

    //Get Node Transformation
    glm::mat4 getNodeTransformation(const std::string& name, aiNode *root = scene->mRootNode);
    glm::mat4 getNodeTransformation(aiNode *leaf, aiNode *root);
    aiNode* getCorrospondingNode(const unsigned int mesh, aiNode *root);
};

#endif //_F_H_MODEL_LOADER_

