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

#include "Model.h"
#include "../Texture/Texture.h"
#include "../Graphics/Graphics.h"

class FModelGroup
{
  private:
    //Buffers
    GLuint vbo;
    GLuint ibo;
    GLuint vao;

    //Models
    std::vector<FModel*> models;
    std::vector<FMaterial*> materials;
  public:
    FModelGroup();
    ~FModelGroup();

    GLvoid readyModelGroup() const;

    GLvoid drawModelGroupGeometry() const;
    GLvoid drawModelGroupTextured() const;

    GLvoid addModel(FModel *model);
    GLvoid addModels(FModel **models, const GLuint modelNum); 
    GLvoid addMaterial(FMaterial *material);
    GLvoid addMaterials(FMaterial **materials, const GLuint materialNum);

    GLvoid finalize();
};

#endif //_F_H_MODEL_GROUP
