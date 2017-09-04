#include "baseGame.hpp"
#include "renderer.hpp"
#include "camera.hpp"
#include <iostream>

BaseGame::BaseGame()
{
  m_Renderer = std::make_shared<Renderer>();
  m_Camera = std::make_shared<Camera>();
}

BaseGame::~BaseGame()
{
}

double lastTime = 0.0;
int lastFrames = 0;
int nbFrames = 0;

void CountFPS()
{
  double currentTime = glfwGetTime();
  nbFrames++;
  if(currentTime - lastTime >= 1.0)
    {
      std::clog << std::string(100, '\b') << nbFrames;
      lastTime = currentTime;
      lastFrames = nbFrames;
      nbFrames = 0;
    }
}

void BaseGame::Start()
{
  std::clog << "Fps:\n";
  lastTime = glfwGetTime();
  while(m_Renderer->IsRunning())
    {
      Update();
      Draw();
    }
  std::clog << "\n";
}

void BaseGame::Update()
{
  CountFPS();
  m_Camera->RotateAroundLookAt(vec3(), vec3(0, 1.0f, 0));

  m_Renderer->Update(lastFrames);
}

void BaseGame::Draw()
{
  mat4 mvp = m_Camera->GetProjection()*m_Camera->GetView();

  m_Renderer->Frame(mvp);
}
