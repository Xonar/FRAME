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

#include "../Graphics/Graphics.h"

#include <glm/glm.hpp>
#include <fstream>
#include <vector>
#include <set>
#include <tuple>
#include <algorithm>
#include <iostream>

FModel::FModel()
{
  vertices = NULL;
  indices = NULL;
  numVertices = numIndices = 0;

  vbo = ibo = 0;

  tTexture = tOverlay = tHeightMap = tNormalMap = 0;
}

FModel::~FModel()
{
  if(vertices)
    delete[] vertices;
  if(indices)
    delete[] indices;

  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &ibo);

  //Don't remove Textures as it is not the model's textures
}


