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

#include <SDL2/SDL_opengl.h>
#include <vector>

class FModelHandler
{
  private:
    //Model Parts
    //Going from high detail to low detail
    std::vector<FModelPart> lodModels;

    //Textures - to be freed on FModelGroup::finalizeModelGroup()
    //           and condensed to an FTexture2DArray
    FTexture2D* tTexture;
    FTexture2D* tHeightMap;
    FTexture2D* tNormalMap;

    GLuint modelIndex; //Used by ModelInstance

  public:
    FModelHandler();
    ~FModelHandler();

    FTexture2D* getTexture(const F_MODEL_TEXTURE_ENUM);

    GLint determineLOD(glm::vec3 distance);
};

#endif // _F_H_MODEL_HANDLER_
