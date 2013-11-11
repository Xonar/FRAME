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

#include <glm/glm.hpp>

#include <SDL2/SDL_opengl.h>

//Functions that convert between assimp classes and glm structs
glm::vec3 aiGLM(aiColor3D col);

template <typename T> glm::vec2 aiGLM(aiVector2t<T> vec);
template <typename T> glm::vec3 aiGLM(aiVector3t<T> vec);
template <typename T> glm::vec4 aiGLM(aiColor4t<T> col);

template <typename T> glm::mat3 aiGLM(aiMatrix3x3t<T> mat);
template <typename T> glm::mat4 aiGLM(aiMatrix4x4t<T> mat);

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
    const GLuint getAnimationCount(const aiScene *s = scene);
    const aiAnimation* getAnimation(const GLuint i,const aiScene *s = scene);

    //Get Mesh[Count]
    const GLuint getMeshCount(const aiScene *s = scene);
    const aiMesh* getMeshCount(const GLuint i, const aiScene *s = scene);

    //Get Bone[Count]
    const GLuint getBoneCount(const aiMesh *m = mesh);
    const aiBone* getBone(const GLuint i, const aiMesh *m = mesh);

    //Get Material[Count]
    const GLuint getMaterialCount(const aiScene *s = scene);
    const aiMaterial* getMaterial(const GLuint i, const aiScene *s = scene);
};

#endif //_F_H_MODEL_LOADER_

