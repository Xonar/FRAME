/*
 * File :
 *      ./Model/Model.cpp
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      Definitions of ./Model/Model.h
 */

#include "Model.h"

FModel::FModel()
{
  this->materialIndex = ~0;
}

FModel::~FModel()
{
  this->materialIndex = ~0;
}

void FModel::createModelFromPartsAndMaterial(FModelPart **parts, GLuint numParts, GLuint material)
{
  this->parts = std::vector<FModelPart*>(parts, parts+numParts);
  this->materialIndex = material;
}

void FModel::drawModel() const
{
  //TODO Draws the correct Part - from Instance data
  //Currently draws first model
  this->parts[0]->drawPart();
}
