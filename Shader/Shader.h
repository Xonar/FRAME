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

#include "../Graphics/Graphics.h"
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

    void printProgramLog(const GLuint program ) const;
    void printShaderLog(const  GLuint shader ) const;
  public:
    FShader();
    ~FShader();

    GLint bind() const;
    void unbind() const;

    GLint loadShader(const std::string &shader, const GLenum type);

    GLint loadProgram();
    void freeProgram();

    //ACCESSOR METHODS
    GLuint getProgram() const { return glProg; };
};

#endif // _F_H_SHADER
