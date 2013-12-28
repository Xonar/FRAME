/*
 * File :
 *      ./Engine/ModelEngine.h
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      Model Engine that handles drawing of models. 
 */

#ifndef _F_H_MODEL_ENGINE_
#define _F_H_MODEL_ENGINE_

#include "../Model/ModelGroup.h"
#include <list>

class FModelEngine
{
  private: 
    std::list<FModelGroup*> modelGroups;
  public:
    FModelEngine();

    void registerModelGroup(FModelGroup* group);

    void drawTextured();
    void drawGeometry();
};

#endif //_F_H_MODEL_ENGINE_
