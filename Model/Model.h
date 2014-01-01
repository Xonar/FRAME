/*
 * File :
 *      ./Model/Model.h
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      The FModel handles FModelParts and acts as a singular Model
 */

#ifndef _F_H_MODEL_
#define _F_H_MODEL_

#include "ModelPart.h"
#include "Model.h"
#include "../Texture/Texture.h"
#include "../Graphics/Graphics.h"
#include "../Material/Material.h"

#include <vector>

class FModel
{
  private:
    //Model Parts - Will be used for lod models
    std::vector<FModelPart*> parts;

    //Material
    GLuint materialIndex;
  public:
    FModel();
    ~FModel();

    void createModelFromPartsAndMaterial(FModelPart **parts, GLuint numParts, GLuint material);
    
    std::vector<FModelPart*>& getParts() { return parts; }
    GLuint getMaterialIndex() const { return this->materialIndex; }

    void drawModel() const;
};

#endif // _F_H_MODEL_
