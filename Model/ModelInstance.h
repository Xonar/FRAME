
/*
 * File :
 *      ./Model/Model.h
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      The FModel class is a handler for Model Objects
 */

#ifndef _F_H_MODEL_INSTANCE_
#define _F_H_MODEL_INSTANCE_

#include "../Container/Container.h"
#include "../Texture/Texture.h"
#include "../Graphics/Graphics.h"

#include <string>

class FModelInstance
{
private:
  //Model this instance is based on
  FModel *pModel;

  //Instance specific data
  glm::vec3 pos;
  glm::vec3 rot;
  glm::vec3 size;

  //TODO Animation Information

  //Overlay
  FTexture *tOverlay;

public:
  FModelInstance(FModel model);

  GLint readyInstance();
}


#endif //_F_H_MODEL_INSTANCE_
