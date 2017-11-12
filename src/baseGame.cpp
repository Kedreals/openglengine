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

void CountFPS()
{
  double currentTime = glfwGetTime();
  lastFrames = floor(1.0/(currentTime-lastTime));
  lastTime = currentTime;
}

void BaseGame::Start()
{
  lastTime = glfwGetTime();
  while(m_Renderer->IsRunning())
    {
      Update();
      Draw();
    }
}

void BaseGame::Update()
{
  CountFPS();
  m_Camera->RotateAroundLookAt(vec3(), 1.0f/(float)lastFrames * vec3(0, 360.0f, 0));

  //m_Renderer->Update(lastFrames);
}

void BaseGame::Draw()
{
  mat4 mvp = m_Camera->GetProjection()*m_Camera->GetView();

  m_Renderer->Frame(mvp);
}
