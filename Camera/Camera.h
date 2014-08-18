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

class FCamera;

#include <glm/glm.hpp>

#include "../Graphics/Graphics.h"

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

    glm::mat4 wvs, svw;
    //Attributes
    bool ready;
    glm::vec3 pos;
    glm::vec3 dir;
    glm::vec3 up;

    //GL Buffers
    GLuint ubo;

    //Functions
    GLint update();
  public:
    FCamera();
    ~FCamera();

    GLvoid setViewPort(const GLint x, const GLint y, const GLint w, const GLint h);

    GLint InitOrthoMatrix(float left,float right,float bottom,float top, float zNear,float zFar);
    GLint InitOrthoMatrix(float left,float right,float bottom,float top);

    GLint InitProjectionMatrix(float vovy, float zNear, float zFar);

    GLvoid setPosition(const glm::vec3 &pos);
    GLvoid lookAt(const glm::vec3 &lookAt);
    GLvoid setDirection(const glm::vec3 &dir);
    GLvoid setUp(const glm::vec3 &up);

    inline glm::vec3 getPosition() const { return this->pos; }
    inline glm::vec3 getDirection() const { return this->dir; }
    inline glm::vec3 getUp() const { return this->up; }

    GLvoid use();

    void bindMatrixUBO(const GLuint block) const;

    void setMatrixUniformBuffer() const;
    void setMatrixUniform(const GLuint uniform) const;

    void setInverseMatrixUniform(const GLuint uniform) const;
    void setPositionUniform(const GLuint uniform);
};

//Global Handle
extern FCamera *gCamera;

#endif // _F_H_CAMERA_
