#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

/** \brief is a simple class reprensenting a camera for rendering
 */
class Camera
{
public:
  /** \brief construct a camera with the given properties
      
      \a position is the position of the camera
      \a lookAt the point the camera looks at
      \a up the vector that detrmines wich direction up is
      \a fov the FoV of the camera
      \a aspect the aspect ratio of the camera
      \a near the near clipping plane
      \a far the far clipping plane
  */
  Camera(
	 const glm::vec3& position = glm::vec3(4,3,3),
	 const glm::vec3& lookAt = glm::vec3(0,0,0),
	 const glm::vec3& up = glm::vec3(0,1,0),
	 float fov = glm::radians(45.0f),
	 float aspect = 1024.0f/768.0f,
	 float near = 0.1f,
	 float far = 100.0f
	 );
  /** \brief default destructor because there is nothing special to destroy
   */
  ~Camera();

  /** \brief returns the view matrix
   */
  const glm::mat4& GetView() const;
  /** \brief returns the projection matrix
   */
  const glm::mat4& GetProjection() const;

  /** \brief returns the position of the camera in world space
   */
  const glm::vec3& GetPosition() const;
  /** \brief returns the direction in which the camera is facing
   */
  const glm::vec3& GetDirection() const;
  /** \brief returns the vector that points up
   */
  const glm::vec3& GetUp() const;
  /** \brief returns the current FoV of the camera

      should only change if setting is changed or you wish to zoom
   */
  const float& GetFoV() const;
  /** \brief returns the current aspect ratio

      should only be changed if a setting was changed
   */
  const float& GetAspect() const;
  /** \brief get the current near plane

      should not change in runtime but possibly could
   */ 
  const float& GetNear() const;
  /** \brief returns the current far cliping plane

      should not change in runtime but possibly could
   */
  const float& GetFar() const;

  /** \brief Set the position of the camera

      Sets the position of the camera and updates the internal view
      matrix
   */
  void SetPosition(const glm::vec3& position);
  /** \brief Set the facing direction

      Sets the orientation of the camera and updates the internal view
      matrix
   */
  void SetDirection(const glm::vec3& direction);
  /** \brief Set the up vector

      Sets the vector that points up and updates the internal view
      matrix
   */
  void SetUp(const glm::vec3& up);

  /** \brief set the FoV of the camera

      Sets the fov and updates the internal projection matrix.
      Could be used for preferneces of views or the use of zooming
   */
  void SetFoV(float fov);
  /** \brief sets the aspect ratio

      Sets the aspect ratio and updates the internal projections matrix
      should only be called when the aspect ratio changes
   */
  void SetAspectRatio(float aspect);
  /** \brief Set the near clipping plane

      Sets the near plane and updates the internal projection matrix
      normaly it should not be called, not because something breaks
      but you should think over your code structure if you call this 
      more than 1 time (may be in initialization).
   */
  void SetNear(float near);
  /** \brief Set the far cliping plane

      Sets the far plane and updates the internal projection matrix
      \sa SetAspectRatio()
   */
  void SetFar(float far);

  /** \brief moves the camera
      
      moves the camera in the given direction
      position = position + direction;
      it also updates the internal view matrix
   */
  void MoveCamera(const glm::vec3& direction);
  /** \brief rotates the camera according to the eulerAngles
      
      \a eulerAngles is a vec3 with the rotation around the x-axis as x-coordinate
      the rotation around the y-axis as y-coordinate and around z-axis as z-coordinate
      \sa RotateCamera(const glm::quat&)
      
   */
  void RotateCamera(const glm::vec3& eulerAngles);
  /** \brief rotates the camera according to the quaternion

      a quaternion is a fast and efficient way to represent a rotation
      \sa RotateCamera(const glm::vec3&)
   */
  void RotateCamera(const glm::quat& rotation);

  /** \brief rotates the position of the camera around the lookAt point.
   */
  void RotateAroundLookAt(const glm::vec3& lookAt, const glm::vec3& rot);
  /** \brief the camera focuses on the given point

      \a point the vec3 that represents the point the camera will look at
   */
  void FocusOn(const glm::vec3& point, const glm::vec3& up = glm::vec3(0,1,0));

private:
  Camera(const Camera&) = delete;
  Camera(Camera&) = delete;
  
private:
  glm::vec3 m_position;
  glm::vec3 m_direction;
  glm::vec3 m_up;
  float m_fov;
  float m_aspect;
  float m_near;
  float m_far;

  glm::mat4 m_view;
  glm::mat4 m_projection;
};

#endif
