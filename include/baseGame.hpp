#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <memory>

class Renderer;
class Camera;

class BaseGame
{
public:
  BaseGame();
  ~BaseGame();
  void Start();

private:
  BaseGame(BaseGame&) = delete;
  BaseGame(const BaseGame&) = delete;

private:
  std::shared_ptr<Renderer> m_Renderer;
  std::shared_ptr<Camera> m_Camera;
};

#endif
