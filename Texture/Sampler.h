/*
 * File :
 *      ./Texture/Sampler.h
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      The FSampler is a handler for all samplers
 */

#ifndef _F_H_SAMPLER_
#define _F_H_SAMPLER_

#include "../Graphics/Graphics.h"

class FSampler
{
private:
  GLuint glSampler;
 
public:
  FSampler();
  ~FSampler();

  void bindSampler();
}

#endif // _F_H_SAMPLER_
