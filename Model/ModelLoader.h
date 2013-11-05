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

#include <SDL2/SDL_opengl.h>

class FModelLoader
{
  private:
    //Cached variables for easier access
    static aiScene* scene;
    static aiMesh* mesh;

  public:
    //Constructor/Deconstructor
    FModelLoader();
    ~FModelLoader();
    
    //Loads Scene and caches scene
    aiScene* loadScene(const std::string path);

    //Get Animation[Count]
    GLint getAnimationCount(const aiScene *s = scene);
    aiAnimation* getAnimation(const GLint i,const aiScene *s = scene);

    //Get Mesh[Count]
    GLint getMeshCount(const aiScene *s = scene);
    aiMesh* getMeshCount(const GLint i, const aiScene *s = scene);

    //Get Bone[Count]
    GLint getBoneCount(const aiMesh *m = mesh);
    aiBone* getBone(const GLint i, const aiMesh *m = mesh);

    //Get Material[Count]
    GLint getMaterialCount(const aiScene *s = scene);
    aiBone* getMaterial(const aiScene *s = scene);
};

#endif //_F_H_MODEL_LOADER_


