#include "camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const glm::vec3& position, const glm::vec3& lookAt, const glm::vec3& up, float fov, float aspect, float near, float far) : m_position(position), m_direction(lookAt-position), m_up(up), m_fov(fov), m_aspect(aspect), m_near(near), m_far(far), m_view(glm::lookAt(position, lookAt, up)), m_projection(glm::perspective(fov, aspect, near, far))
{
}

Camera::~Camera()
{
}

const glm::mat4& Camera::GetView() const
{
  return m_view;
}

const glm::mat4& Camera::GetProjection() const
{
  return m_projection;
}

const glm::vec3& Camera::GetPosition() const
{
  return m_position;
}

const glm::vec3& Camera::GetDirection() const
{
  return m_direction;
}

const glm::vec3& Camera::GetUp() const
{
  return m_up;
}

const float& Camera::GetFoV() const
{
  return m_fov;
}

const float& Camera::GetAspect() const
{
  return m_aspect;
}

const float& Camera::GetNear() const
{
  return m_near;
}

const float& Camera::GetFar() const
{
  return m_far;
}

void Camera::SetPosition(const glm::vec3& position)
{
  m_position = position;
  m_view = glm::lookAt(m_position, m_position+m_direction, m_up);
}

void Camera::SetDirection(const glm::vec3& direction)
{
  m_direction = direction;
  m_view = glm::lookAt(m_position, m_position+m_direction, m_up);
}

void Camera::SetUp(const glm::vec3& up)
{
  m_up = up;
  m_view = glm::lookAt(m_position, m_position+m_direction, m_up);
}

void Camera::SetFoV(float fov)
{
  m_fov = fov;
  m_projection = glm::perspective(m_fov, m_aspect, m_near, m_far);
}

void Camera::SetAspectRatio(float aspect)
{
  m_aspect = aspect;
  m_projection = glm::perspective(m_fov, m_aspect, m_near, m_far);
}

void Camera::SetNear(float near)
{
  m_near = near;
  m_projection = glm::perspective(m_fov, m_aspect, m_near, m_far);
}

void Camera::SetFar(float far)
{
  m_far = far;
  m_projection = glm::perspective(m_fov, m_aspect, m_near, m_far);
}

void Camera::MoveCamera(const glm::vec3& direction)
{
  SetPosition(m_position + direction);
}

void Camera::RotateCamera(const glm::vec3& eulerAngles)
{
  glm::quat rot(eulerAngles);
  RotateCamera(rot);
}

void Camera::RotateCamera(const glm::quat& rot)
{
  SetDirection(rot*m_direction);
  SetUp(rot*m_up);
}

void Camera::RotateAroundLookAt(const glm::vec3& lookAt, const glm::vec3& rotation)
{
  glm::vec3 p = m_position-lookAt;
  
  glm::quat rot((3.14f/180.0f)*rotation);
  SetPosition(rot*p);
  FocusOn(lookAt);
}

void Camera::FocusOn(const glm::vec3& point, const glm::vec3& up)
{
  SetDirection(point-m_position);
  SetUp(up);
}

