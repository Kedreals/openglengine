#ifndef _RENDERER_HPP_
#define _RENDERER_HPP_

class Game;
class Model;

/** \todo implement
 */
class Renderer
{
public:
  Renderer();
  ~Renderer();

  void Initialize();
  void Draw(const Model& model);

protected:
  void DrawToScreen() const;
  friend class Game;

private:
std::vector<glm::vec3>
};

#endif //_RENDERER_HPP_
