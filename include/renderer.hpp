#ifndef _RENDERER_HPP_
#define _RENDERER_HPP_


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "model.hpp"

using namespace glm;

class Model;

/** \todo implement
 */
class Renderer
{
public:
  Renderer(unsigned int width = 1024, unsigned int height = 768);
  ~Renderer();

  bool IsRunning() const;
  void Update();
  void Frame(mat4 mvp);
  
  
private:
  Renderer(Renderer&) = delete;
  Renderer(const Renderer&) = delete;
  
private:
  GLFWwindow* m_window;
  bool m_initialized = false;
  /*GLuint m_vertexArrayID;
  GLuint m_vertexBuffer;
  GLuint m_colorBuffer;
  GLuint m_indexBuffer;
  */
  GLuint m_shader;
  GLuint m_mvp_handle;
  Model m_model1;
  Model m_model2;
};

#endif //_RENDERER_HPP_
