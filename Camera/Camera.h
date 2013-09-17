/*
 * File :
 *      ./Camera/Camera.h
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      The Camera class is a handler for the a camera Object
 */

#ifndef _F_H_CAMERA_
#define _F_H_CAMERA_

#include <glm/glm.hpp>

#include <SDL2/SDL_opengl.h>

class FCamera
{
  private:

    //Viewport
    int x,y;
    int width;
    int height;
    float aspect;

    //Matrix
    glm::mat4 WorldViewMatrix;
    bool updateWorldViewMatrix;

    glm::mat4 ViewScreenMatrix; //Projection or Ortho
    bool updateViewScreenMatrix;  
    //Attributes
    bool ready;
    glm::vec3 pos;
    glm::vec3 dir;

    //GL Buffers
    GLuint ubo;

    //Functions
    GLint updateUBO();
  public:
    FCamera();
    ~FCamera();

    GLint InitOrthoMatrix(float left,float right,float bottom,float top, float near,float far);
    GLint InitOrthoMatrix(float left,float right,float bottom,float top);

    GLint InitProjectionMatrix(float vovy, float zNear, float far);

    void setMatrixUniformBlock();
    void setMatrixUniformWorldView(GLuint uniform);
    void setMatrixUniformViewScreen(GLuint uniform);
};

#endif // _F_H_CAMERA_
