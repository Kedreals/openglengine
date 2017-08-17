#include "baseGame.hpp"
#include "camera.hpp"
#include <iostream>

BaseGame::BaseGame(int width, int height) : camera(nullptr), m_window(nullptr), m_continue(true)
{
  InitGLFW(width, height);
  
  Initialize();
  LoadContent();
}

BaseGame::~BaseGame()
{
  glfwTerminate();
  m_window = nullptr;
  if(camera)
    delete camera;
}

void BaseGame::Exit(const std::string& error)
{
  std::cerr << error << "\n";
  m_continue = false;
}

void BaseGame::Initialize()
{
  camera = new Camera();
  if(!camera)
    Exit("cannot initialize Camera");
}

void BaseGame::LoadContent()
{
}

void BaseGame::Update()
{
}

void BaseGame::Draw()
{
}

void BaseGame::InitGLFW(int width, int height, const std::string& title)
{
  if(!glfwInit())
    {
      Exit("Failed to initialize GLFW");
    }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
  if(m_window == nullptr)
    {
      Exit("Failed to open GLFW window.");
    }
  glfwMakeContextCurrent(m_window);
  glewExperimental = true;
  if(glewInit() != GLEW_OK)
    {
      Exit("Failed to initialize GLEW");
    }

  glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);

  glClearColor(0,0,0,0);
}

void BaseGame::Start()
{
  do{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    Update();
    Draw();

    glfwSwapBuffers(m_window);
    glfwPollEvents();
    
  }while(m_continue &&
	 glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
	 !glfwWindowShouldClose(m_window));
}
