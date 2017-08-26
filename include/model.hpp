#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/** \todo implement
    \brief simple class containing all needed informations about a model

    contains the transformation matrix for getting from Model space
    to world space
 */
class Model
{
public:
  Model();
  ~Model();

  bool Initialize();

  void Translate(const glm::vec3& translation);
  void Scale(float scaling);
  void SetScale(float s);
  
  void Draw(const glm::mat4& mvp, GLuint shader, GLuint mvp_handle);

private:
  float m_Scale = 1.0f;
  glm::mat4 m_World;
  bool m_initialized;
  GLuint m_vertexArrayID;
  GLuint m_vertexBuffer;
  GLuint m_colorBuffer;
  GLuint m_indexBuffer;
};

#endif
