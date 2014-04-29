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
#include <map>

class FShader
{
  private:
    GLuint glProg;

    GLuint  vs, //Vertex Shader
            gs, //Geometry Shader
            tc, //Tesselation Control
            te, //Tesselation Evaluation
            fs; //Fragment Shader

    //Reference to Self in ShaderManager
    std::map<std::string, FShader*>::iterator ref;

  public:
    FShader();
    ~FShader();

    //State Functions
    GLint bind() const;
    void unbind() const;

    //Shader Functions
    GLint loadShader(const std::string &shader, const GLenum type);
    GLuint getShader(const GLenum type);

    //Program Functions
    GLint loadProgram();
    void freeProgram();

    //ACCESSOR METHODS
    GLuint getProgram() const { return glProg; };

    //Shader Logs
    static void printProgramLog(const GLuint program );
    static void printShaderLog(const  GLuint shader );
};

#endif // _F_H_SHADER
