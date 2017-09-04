#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "vertex.hpp"
#include <glm/gtc/quaternion.hpp>

#include <vector>

/** \brief simple class containing all needed informations about a model

    contains the transformation matrix for getting from Model space
    to world space, also contains all information for actualy drawing it.
 */
class Model
{
public:
  /** \todo implement model loader
      \brief simple ctor. In the future it should be able to load from files.
  */
  Model(const char* file = "");
  /** \brief simple dtor, cleans up all needed buffers
  */
  ~Model();

  /** \brief initializes the model for drawing

      generates a vertex buffer and an indexbuffer and fills
      them.
  */
  bool Initialize();

  /** \brief translates the Model by \a translation
  */
  void Translate(const glm::vec3& translation);
  /** \brief scales the model uniformaly by \a scaling

      it ignores earlier scalings. e.g. if you have a model m
      and call m.Scale(0.5f) than it will be scaled to half the size of
      of the original. If you than call m.Scale(0.5f) again, nothing happens
      and the model is still at half the size of the original.
  */
  void Scale(float scaling);

  /** \todo implement
   */
  void Rotate(const glm::vec3& eulerAngles);
  /** \todo implement
   */
  void Rotate(const glm::quat& rotation);

/** \brief draws the Model.

    \a mvp the Projection*View*World Matrix. It will be multiplied by the 
    World Matrix of the model.
 */
  void Draw(const glm::mat4& mvp, GLuint shader, GLuint mvp_handle);

private:
  Model(Model&) = delete;
  Model(const Model&) = delete;
  
private:
  float m_Scale = 1.0f;
  glm::quat m_orientation;
  glm::mat4 m_World;
  bool m_initialized;
  std::vector<Vertex> m_vertecies;
  std::vector<unsigned int> m_indices;

  GLuint m_vertexArrayID;
  GLuint m_vertexBuffer;
  GLuint m_colorBuffer;
  GLuint m_indexBuffer;
  
};

#endif
