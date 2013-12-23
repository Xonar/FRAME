/*
 * File :
 *      ./Model/ModelHandler.h
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      The FModelHandler handles FModelParts and acts as a singular Model
 */

#ifndef _F_H_MODEL_HANDLER_
#define _F_H_MODEL_HANDLER_

#include "ModelPart.h"
#include "Model.h"
#include "../Texture/Texture.h"
#include "../Graphics/Graphics.h"
#include "../Material/Material.h"

#include <vector>

class FModelHandler
{
  private:
    //Model Parts
    //Going from high detail to low detail
    std::vector<FModelPart> lodModels;

    //Material
    GLuint materialIndex;

    GLuint modelIndex; //Used by ModelInstance

  public:
    FModelHandler();
    ~FModelHandler();

    FTexture2D* getTexture(const F_MODEL_TEXTURE_ENUM);

    GLint determineLOD(glm::vec3 distance);
};

#endif // _F_H_MODEL_HANDLER_
