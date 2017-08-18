#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "model.hpp"
#include "debug.hpp"

class Camera;

/** \brief a simple class representing the typical game
    
    opens a window.
*/
class BaseGame
{
public:
  /** \brief ctor of a base game

      \a width representing the start width of the window
      \a height representing the start height of the window
   */
  BaseGame(int width = 1024, int height = 768);
  ~BaseGame();

  /** \brief Start the game loop

      continues (to clear the depth buffer and the screen
      than calls Update, than Draw and
      finaly presenting the result) until either Exit is called
      or Escape or x(the close button from the window) is pressed.
   */
  void Start();  
  
protected:
  /** \brief signals the game that the current itteration is the last

      sets a bool so that the current itteration is the last itteration
      of the game loop and writes \a error in the std::cerr
   */
  void Exit(const std::string& error = "");

  /** \brief Initialize all needed Attributes of the game
   */
  void Initialize();
  /** \brief Loads all needed Content for the game
   */
  void LoadContent();
  /** \brief Updates the content for this frame
   */
  void Update();
  /** \brief Draws the content

      \todo build a Renderer for more efficient Draw calls
   */
  void Draw();

  
private:
  BaseGame(const BaseGame&) = delete;
  BaseGame(BaseGame&) = delete;
  BaseGame& operator =(const BaseGame&) = delete;

  void InitGLFW(int width, int height, const std::string& title = "Engine");

protected:
  /** \brief Camera of the game
   */
  Camera* camera;
  
private:
  GLFWwindow* m_window;
  bool m_continue;
  Model* m_Model;
  GLuint m_shader;
  GLuint m_mvp_handle;
};

#endif
