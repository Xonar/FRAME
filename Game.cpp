/*
 * File :
 *      ./Game.cpp
 *
 * Author : 
 *      Xonar <Paul le Roux>
 *
 * Description :
 *      Definitions of ./Game.h
 *
 */

#include "Game.h"
#include "Global.h"
#include "Texture/Texture.h"
#include "Model/Model.h"
#include "Model/ModelLoader.h"
#include "Material/Material.h"
#include "Camera/Camera.h"
#include "Graphics/Graphics.h"
#include "Lib/FGLext.h"
#include "Container/Container.h"
#include "Time/Time.h"
#include "Lib/Log.h"

//TODO Temp Resources
FModel **models;
int modelNum;

FModelGroup *modelGroup;

FMaterial **materials;
int materialNum;

FCamera *gCamera = NULL;

FShader *shader = NULL;

FFont *font = NULL;

GLint initializeGame()
{
  //Load Scene
  FModelLoader loader = FModelLoader();
  const aiScene *scene = loader.loadScene("Assets/Beach.dae");
  
  //Log Information
  gLogv << "Model File : " << "Assets/Beach.dae" << std::endl;
  gLogv << "\tLights : " << scene->mNumLights << " (IGNORED)" << std::endl;
  gLogv << "\tAnimations : " << scene->mNumAnimations << " (IGNORED)" << std::endl;
  gLogv << "\tMaterials : " << scene->mNumMaterials << " (PARTIALLY IMPLEMENTED)" << std::endl;
  gLogv << "\tMeshes : " << scene->mNumMeshes << std::endl;
  gLogv << "\tCameras : " << scene->mNumCameras << std::endl;
  gLogv << "\tTextures : " << scene->mNumTextures << " (IGNORED)" << std::endl;

  //Set Camera
  if(scene->mNumCameras < 1)
  {
    //Create Default Camera
    gLogv << "Using Default Camera" << std::endl;
    gCamera = new FCamera();

    gCamera->setViewPort(0,0,gWindow->getWindowWidth(),gWindow->getWindowHeight());
    gCamera->setPosition(glm::vec3(4.f,3.f,-3.f));
    gCamera->lookAt(glm::vec3(0.f,0.f,0.f));
    gCamera->InitProjectionMatrix(45.f,0.1f,100.f);
  }
  else
  {
    //Create Camera from scene data
    gLogv << "Using Camera from model file" << std::endl;
    if(scene->mNumCameras > 1)
      gLogv << "\tIgnoring cameras after camera 1" << std::endl;
    gCamera = loader.getCamera(0,scene);
  }

  //Load ModelParts
  models = new FModel*[loader.getMeshCount()];

  for(GLuint i = 0;i < loader.getMeshCount();i++)
    models[i] = loader.getMesh(i);

  modelNum = loader.getMeshCount();

  //Load Materials
  materials = new FMaterial*[loader.getMaterialCount()];

  for(GLuint i = 0; i < loader.getMaterialCount();i++)
    materials[i] = loader.getMaterial(i);

  materialNum = loader.getMaterialCount();

  //Create Model Group
  modelGroup = new FModelGroup();
  modelGroup->addModels(models, modelNum);
  modelGroup->addMaterials(materials, materialNum);
  modelGroup->finalize();

  gModelEngine->registerModelGroup(modelGroup);

  //FFont
  font = new FFont();
  font->createFromTTF("Assets/newscycle-regular.ttf", 18);

  gFontEngine->addFont(font);
  
  return 0;
}

GLvoid updateGame()
{
  //Draw some text
  font->drawText("Beach Scene DEMO", glm::vec2( 10, 10) );
}
