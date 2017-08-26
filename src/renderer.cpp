#include "renderer.hpp"
#include "shader.hpp"
#include <iostream>

Renderer::Renderer(unsigned int width, unsigned int height)
{
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

  m_window = glfwCreateWindow(width, height, "Engine", nullptr, nullptr);
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

  /* glGenVertexArrays(1, &m_vertexArrayID);
  glBindVertexArray(m_vertexArrayID);
  */

  m_model1 = Model();
  m_model1.Initialize();

  m_model1.Scale(0.5f);
  m_model1.Translate(glm::vec3(-0.5f, -0.5f, -0.5f));

  m_model2 = Model();
  m_model2.Initialize();

  m_model2.Scale(0.5f);
  m_model2.Translate(glm::vec3(0.5f, 0.5f, 0.5f));
  
  m_shader = LoadShaders("../shaders/SimpleVertexShader.vs", "../shaders/SimpleFragmentShader.fs");

  m_mvp_handle = glGetUniformLocation(m_shader, "MVP");

  
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_CULL_FACE);

  
  m_initialized = true;
}

Renderer::~Renderer()
{
  /*glDeleteBuffers(1, &m_vertexBuffer);
  glDeleteBuffers(1, &m_colorBuffer);
  glDeleteBuffers(1, &m_indexBuffer);
  
  glDeleteVertexArrays(1,&m_vertexArrayID);
  */
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

void Renderer::Update()
{
  t += 0.1f;
  m_model1.Scale(std::cos(t)*0.25f + 0.5f);
  m_model2.Scale(std::sin(t*1.5f)*0.25f + 0.5f);
}

void Renderer::Frame(mat4 mvp)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  /* glBindVertexArray(m_vertexArrayID);

  glUseProgram(m_shader);

  glUniformMatrix4fv(m_mvp_handle, 1, GL_FALSE, &mvp[0][0]);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);

  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
  glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0);

  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
  glVertexAttribPointer(
			1,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0);

  glDrawElements(
		 GL_TRIANGLES,
		 36,
		 GL_UNSIGNED_INT,
		 (void*)0);
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  */

  m_model1.Draw(mvp, m_shader, m_mvp_handle);
  m_model2.Draw(mvp, m_shader, m_mvp_handle);
  
  glfwSwapBuffers(m_window);
  glfwPollEvents();
}
