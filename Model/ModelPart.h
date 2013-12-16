/*
 * File :
 *      ./Model/ModelPart.h
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      The FModelPart class is a handles Parts of a Model
 */

#ifndef _F_H_MODEL_PART_
#define _F_H_MODEL_PART_

#include "../Container/Container.h"
#include "../Texture/Texture.h"
#include "../Graphics/Graphics.h"

#include <vector>
#include <string>

class FModelPart
{
  private:
    //Model Data   
    std::vector<FVertex3> vertices;
    std::vector<GLuint> indices;

    //Data required for draw
    GLuint baseVertex;
    GLuint indicesCount;
    GLuint indicesStart;
  public:
    FModelPart();
    ~FModelPart();

    const std::vector<FVertex3>& getVertices() const;
    const std::vector<GLuint>& getIndices() const;

    FVertex3* getVerticesCopy() const;
    GLuint* getIndicesCopy() const;

    GLvoid releaseVertices();
    GLvoid releaseIndices();

    GLint loadModelPartFromVertices(FVertex3* const vertices,const GLuint numVertices);
    GLint loadModelPartFromVerticesAndIndices(FVertex3 *const vertices, const GLuint numVertices,
                                              GLuint* const indices, const GLuint numIndices);
    GLint loadModelPartFromVertexAndTextureArray(const GLfloat* const vertices,
                                                const GLfloat* const uvs, const GLuint numVertices);
    GLint loadModelPartFromVertexTextureAndNormalArray(const GLfloat* const vertices,
                                                const GLfloat* const uvs, const GLfloat* const norm,
                                                const GLuint numVertices);
};

#endif //_F_H_MODEL_PART_
