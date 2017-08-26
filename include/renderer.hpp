#ifndef _RENDERER_HPP_
#define _RENDERER_HPP_

#include <glm/glm.hpp>

//class Model;

/** \todo implement
 */
class Renderer
{
public:
  Renderer();
  ~Renderer();

  void Initialize();
  //void AddContent(const Model& model);
  void Draw() const;
  
private:
  std::vector<const Model&> m_models;
  GLuint m_vertexBuffer;
  GLuint m_colorBuffer;
  GLuint m_indexBuffer;
  GLuint m_vertexArrayID;
};

#endif //_RENDERER_HPP_
