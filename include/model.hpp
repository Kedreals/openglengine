#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <vector>

#include <GL/glew.h>

class Camera;

/** \todo implement
    \brief simple class containing all needed informations about a model

    contains the transformation matrix for getting from Model space
    to world space
 */
class Model
{
public:
  Model(const std::string& filePath = "");
  Model(const Model&);
  Model(Model&);
  ~Model();
  Model& operator =(const Model&);

  void Translate(const glm::vec3& translation);
  void Rotate(const glm::vec3& eulerangles);
  void Rotate(const glm::quat& rotation);
  void Scale(const glm::vec3& scaling);

  void SetPosition(const glm::vec3& position);
  void SetOrientation(const glm::vec3& eulerangles);
  void SetOrientation(const glm::quat& orientation);
  void SetScale(const glm::vec3& scale);

  const glm::vec3& GetPosition() const;
  const glm::quat& GetOrientation() const;
  const glm::vec3& GetScaling() const;

  glm::mat4 GetWorldMatrix() const;

  void Draw(const Camera&, GLuint programID = 0, GLuint mvp_handle = 0) const;

  GLfloat* GetPositions(int* count) const;
  GLfloat* GetColors(int* count) const;
  unsigned int* GetIndices(int* count) const;

private:
  glm::vec3 m_position;
  glm::quat m_orientation;
  glm::vec3 m_scaling;

  std::vector<glm::vec3> m_vertexPositions;
  std::vector<glm::vec3> m_vertexColors;
  std::vector<unsigned int> m_indices;
};

#endif
