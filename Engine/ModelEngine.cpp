/*
 * File :
 *      ./Engine/ModelEngine.cpp
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      Definitions of ./Engine/ModelEngine.h
 */

#include "ModelEngine.h"

FModelEngine::FModelEngine()
{
}

void FModelEngine::drawGeometry()
{
  for(const FModelGroup *it : this->modelGroups)
  {
    it->readyModelGroup();
    it->drawModelGroupGeometry();
  }
}

void FModelEngine::drawTextured()
{
  for(const FModelGroup *it : this->modelGroups)
  {
    it->readyModelGroup();
    it->drawModelGroupTextured();
  }
}

void FModelEngine::registerModelGroup(FModelGroup* group)
{
  this->modelGroups.push_back(group);
}
