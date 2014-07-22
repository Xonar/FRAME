/*
 * File :
 *      ./Camera/PlayerFreeCamera.h
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      Free Floating Camera Movements
 */

#ifndef _F_H_PLAYERFREECAMERA_
#define _F_H_PLAYERFREECAMERA_

class FPlayerFreeCamera;

#include "Camera.h"

class FPlayerFreeCamera
{
  private:
    //Camera that Player Controls
    FCamera* camera;
  public:
    //Constructor
    FPlayerFreeCamera(FCamera* camera);

    //Update Camera based on Input
    void update();
};

#endif // _F_H_PLAYERFREECAMERA_
