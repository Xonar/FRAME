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
    GLuint ubViewScreen;
    GLuint ubWorldView;

    //Functions
    GLint updateUBO();
  public:
    FCamera();
    ~FCamera();

    GLvoid setViewPort(const GLint x, const GLint y, const GLint w, const GLint h);

    GLint InitOrthoMatrix(float left,float right,float bottom,float top, float near,float far);
    GLint InitOrthoMatrix(float left,float right,float bottom,float top);

    GLint InitProjectionMatrix(float vovy, float zNear, float far);

    GLvoid setPosition(const glm::vec3 &pos);
    GLvoid lookAt(const glm::vec3 &lookAt);
    GLvoid setDirection(const glm::vec3 &dir);

    void setMatrixUniform(const GLuint worldView, const GLuint viewScreen);
    void setMatrixUniformWorldView(const GLuint uniform);
    void setMatrixUniformViewScreen(const GLuint uniform);
};

#endif // _F_H_CAMERA_
