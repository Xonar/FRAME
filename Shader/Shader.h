/*
 * File :
 *      ./Shader/Shader.h
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      The FShader class is a handler for all OpenGL shaders
 */

#ifndef _F_H_SHADER_
#define _F_H_SHADER_

#include <SDL2/SDL_opengl.h>
#include <string>

class FShader
{
  private:
    GLuint glProg;

    GLuint  vs, //Vertex Shader
            gs, //Geometry Shader
            tc, //Tesselation Control
            te, //Tesselation Evaluation
            fs; //Fragment Shader

    void printProgramLog( GLuint program );
    void printShaderLog( GLuint shader );
  public:
    FShader();
    ~FShader();

    GLint bind();
    void unbind();

    GLint loadShader(std::string shader, GLenum type);
    void freeProgram();
};

#endif // _F_H_SHADER
