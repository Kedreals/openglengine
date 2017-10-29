#include "renderer.hpp"
#include "shader.hpp"
#include <iostream>

Renderer::Renderer(unsigned int width, unsigned int height, const char* title)
{
  m_baseTitle = title;
  
  if(!glfwInit())
    {
      std::cerr << "Failed to initialize GLFW\n";
      return;
    }
  
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
  if(!m_window)
    {
      std::cerr << "Failed to open GLFW window.\n";
      return;
    }
  glfwMakeContextCurrent(m_window);
  
  glewExperimental = true;
  if(glewInit() != GLEW_OK)
    {
      std::cerr << "Failed to initialize GLEW\n";
      return;
    }
  
  glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);
  
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  
  std::shared_ptr<Model> model1 = std::make_shared<Model>("../data/gargoyle500.off");
  model1->Initialize();

  //  model1->Scale(0.5f);
  // model1->Translate(glm::vec3(-0.5f, -0.5f, -0.5f));
  
  //std::shared_ptr<Model> model2 = std::make_shared<Model>();
  //model2->Initialize();
  
  //model2->Scale(0.5f);
  // model2->Translate(glm::vec3(0.5f, 0.5f, 0.5f));
  
  AddContent(model1);
  //  AddContent(model2);
  
  m_shader = LoadShaders("../shaders/SimpleVertexShader.vs", "../shaders/SimpleFragmentShader.fs");
  
  m_mvp_handle = glGetUniformLocation(m_shader, "MVP");
  
  
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_CULL_FACE);
  
  m_initialized = true;
}

Renderer::~Renderer()
{
  glDeleteProgram(m_shader);

  glfwTerminate();
}

bool Renderer::IsRunning() const
{
  if(!m_initialized)
    return false;

  return glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(m_window);
}

float t = 0;

void Renderer::Update(int fps)
{
  t += 1.0f;
  float time = 1.0f/fps;
  for(size_t i = 0; i < m_Content.size(); ++i)
    {
      
      vec3 euler(1,1,1);
      m_Content[i]->Rotate(time*euler);
    }
  
  std::string title = m_baseTitle + " FPS: ";
  title += std::to_string(fps);
  
  SetTitle(title);
  
}

void Renderer::Frame(const mat4& vp)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  for(auto m : m_Content)
    m->Draw(vp, m_shader, m_mvp_handle);
  
  glfwSwapBuffers(m_window);
  glfwPollEvents();
}
 
void Renderer::SetTitle(const std::string& title)
{
  //glfwSetWindowTitle(m_window, title.c_str()); it is evil!!!
  std::clog << title << std::endl;
}

void Renderer::AddContent(std::shared_ptr<Model> model)
{
  m_Content.push_back(model);
}
