#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <memory>

class Renderer;
class Camera;

/** \brief the base class for a game

 */
class BaseGame
{
public:
  /** \brief basic ctor
   */
  BaseGame();
  /** \brief basic dtor
   */
  ~BaseGame();
  /** \brief Starts the main gameloop
   */
  void Start();

protected:
  /** \brief Updates the content of the game.

      It is called before the Draw.
   */
  virtual void Update();

  /** \brief Draws the content of one Frame

      It is called after Update
   */
  virtual void Draw();
private:
  BaseGame(BaseGame&) = delete;
  BaseGame(const BaseGame&) = delete;

private:
  std::shared_ptr<Renderer> m_Renderer;
  std::shared_ptr<Camera> m_Camera;
};

#endif
