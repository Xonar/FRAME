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
#include "Camera/Camera.h"
#include "Graphics/Graphics.h"
#include "Lib/FGLext.h"
#include "Container/Container.h"
#include "Time/Time.h"
#include "Lib/Log.h"

//TODO Temp Resources
FModel **models;
int modelNum;

FCamera *camera;

GLuint uniformViewScreenMatrix = 0;
GLuint uniformWorldViewMatrix = 0;
GLuint uniformOrthoMatrix = 0;
GLuint uniformFontSampler = 0;

FTexture2D *tex = NULL;
GLint uniformTextureSampler = 0;

FShader *shader = NULL;

FFont *font = NULL;

GLint initializeGame()
{
  //Create Shader
  shader = new FShader();

  shader->loadShader("Shader/FX/3D/3DForward.glvs",GL_VERTEX_SHADER);
  shader->loadShader("Shader/FX/3D/3DForward.glfs",GL_FRAGMENT_SHADER);

  shader->loadProgram();

  //Load Scene
  FModelLoader loader = FModelLoader();
  const aiScene *scene = loader.loadScene("Assets/Beach.dae");
  
  //Log Information
  gLogv << "Model File : " << "Assets/Beach.dae" << std::endl;
  gLogv << "\tLights : " << scene->mNumLights << " (IGNORED)" << std::endl;
  gLogv << "\tAnimations : " << scene->mNumAnimations << " (IGNORED)" << std::endl;
  gLogv << "\tMaterials : " << scene->mNumMaterials << " (IGNORED)" << std::endl;
  gLogv << "\tMeshes : " << scene->mNumMeshes << std::endl;
  gLogv << "\tCameras : " << scene->mNumCameras << std::endl;
  gLogv << "\tTextures : " << scene->mNumTextures << " (IGNORED)" << std::endl;

  //Set Camera
  if(scene->mNumCameras < 1)
  {
    //Create Default Camera
    gLogv << "Using Default Camera" << std::endl;
    camera = new FCamera();

    camera->setViewPort(0,0,gWindow->getWindowWidth(),gWindow->getWindowHeight());
    camera->setPosition(glm::vec3(4.f,3.f,-3.f));
    camera->lookAt(glm::vec3(0.f,0.f,0.f));
    camera->InitProjectionMatrix(45.f,0.1f,100.f);
  }
  else
  {
    //Create Camera from scene data
    gLogv << "Using Camera from model file" << std::endl;
    if(scene->mNumCameras > 1)
      gLogv << "\tIgnoring cameras after camera 1" << std::endl;
    camera = loader.getCamera(0,scene);
  }

  //Load ModelParts
  FModelPart** parts = new FModelPart*[loader.getMeshCount()];

  for(GLuint i = 0;i < loader.getMeshCount();i++)
    parts[i] = loader.getMesh(i);

  //Load Models
  models = new FModel*[loader.getMeshCount()];

  for(GLuint i = 0;i < loader.getMeshCount();i++)
  {
    models[i] = new FModel();
    models[i]->loadModelFromPart(parts[i]);
  }

  modelNum = loader.getMeshCount();

  uniformViewScreenMatrix = glGetUniformLocation(shader->getProgram(), "ViewScreenMatrix" );
  uniformWorldViewMatrix = glGetUniformLocation(shader->getProgram(), "WorldViewMatrix" );
 
  //Set Model Uniform Matrices
  shader->bind();
  camera->use();
  camera->setMatrixUniform(uniformWorldViewMatrix, uniformViewScreenMatrix);

  //Set OpenGL Variables
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  //FFont
  font = new FFont();
  font->createFromTTF("Assets/TakaoPGothic.ttf", 18);

  gFontEngine->addFont(font);
  
  //Other
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  return 0;
}

GLvoid drawGame()
{
  //ENABLE Depth Test and Cull
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);

  //Bind Shader
  shader->bind();

  //Setup Screen Matrix
  camera->use();

  //Draw Models
  for(int i = 0;i < modelNum;i++)
  {
    //Ready
    models[i]->readyDraw();

    //Render
    models[i]->draw();
  }

  //Draw some text
  font->drawText("Beach Scene DEMO", glm::vec2( 10, 10) );
}
