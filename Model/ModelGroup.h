/*
 * File :
 *      ./Model/ModelGroup.h
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      The FModelGroup handles Model Groups
 */

#ifndef _F_H_MODEL_GROUP_
#define _F_H_MODEL_GROUP_

#include "ModelHandler.h"
#include "../Texture/Texture.h"
#include "../Graphics/Graphics.h"

class FModelGroup
{
  private:
  
    //Buffers
    GLuint vbo;
    GLuint ibo;
    GLuint vao;

    //Texture Objects
    FTexture2DArray *tTexture;
    FTexture2DArray *tHeightMap;
    FTexture2DArray *tNormalMap;

    //Models
    std::vector<FModelHandler> models;
  public:
    FModelGroup();
    ~FModelGroup();

    GLvoid readyModelGroup() const;
    GLvoid readyModelGroupTextures() const;

    GLvoid drawModelGroup() const;

    GLvoid addModelHandler(const FModelHandler& handler);
    GLvoid finalizeModelGroup();
};

#endif //_F_H_MODEL_GROUP
