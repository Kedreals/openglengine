#ifndef _RENDERER_HPP_
#define _RENDERER_HPP_

#include <string>
#include <memory>

#include "model.hpp"

using namespace glm;

class Model;

/** \todo Add more Setter and Getter functions
    \brief simple class for Rendering Content to the window
    
*/
class Renderer
{
public:
  /** \brief Initializes a window and the glfw stuff
   */
  Renderer(unsigned int width = 1024, unsigned int height = 768, const char* title = "Engine");
  /** \brief terminates the glfw library
   */
  ~Renderer();

  /** \brief returns bool if the window is still open
   */
  bool IsRunning() const;
  /** \brief updates the content

      may be obsoleat soon.
   */
  void Update(int fps);
  /** \brief renders the content.

      \a mvp is the projection*view*Model Matrix defining how to render the content.
      \sa Model::Draw()
   */
  void Frame(const mat4& mvp);

  /** \brief Sets the title of the window
  */
  void SetTitle(const std::string& title);

  /** \brief Add the \a model to the Content that is drawn each frame
  */
  void AddContent(std::shared_ptr<Model> model);
  
private:
  Renderer(Renderer&) = delete;
  Renderer(const Renderer&) = delete;
  
private:
  std::string m_baseTitle;
  GLFWwindow* m_window;
  bool m_initialized = false;
  
  GLuint m_shader;
  GLuint m_mvp_handle;
  std::vector<std::shared_ptr<Model>> m_Content;
};

#endif //_RENDERER_HPP_
