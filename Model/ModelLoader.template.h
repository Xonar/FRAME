#include <glm/gtc/type_ptr.hpp>

template <typename T> glm::vec2 aiGLM(aiVector2t<T> vec)
{
  return glm::vec2(vec.x, vec.y);
}

template <typename T> glm::vec3 aiGLM(aiVector3t<T> vec)
{
  return glm::vec3(vec.x, vec.y, vec.z);
}

template <typename T> glm::vec4 aiGLM(aiColor4t<T> col)
{
  return glm::vec4(col.r, col.g, col.b, col.a);
}

template <typename T> glm::mat3 aiGLM(aiMatrix3x3t<T> mat)
{
  return glm::transpose(glm::make_mat3(&mat[0][0]));
}

template <typename T> glm::mat4 aiGLM(aiMatrix4x4t<T> mat)
{
  return glm::transpose(glm::make_mat4(&mat[0][0]));
}
