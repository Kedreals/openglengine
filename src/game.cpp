#include "baseGame.hpp"
#include "camera.hpp"
#include "shader.hpp"
#include <iostream>

BaseGame::BaseGame(int width, int height) : camera(nullptr), m_window(nullptr), m_continue(true), m_Model(nullptr)
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
  if(m_Model)
    delete m_Model;
}

void BaseGame::Exit(const std::string& error)
{
  std::cerr << error << "\n";
  m_continue = false;
}

GLuint mvp_handle;

GLuint VertexArrayID;
GLuint vertexbuffer;
GLuint colorbuffer;
GLuint elementbuffer;

void BaseGame::Initialize()
{
   glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

   //Create and compile our GLSL program from the shaders
  m_shader = LoadShaders("../shaders/SimpleVertexShader.vs", "../shaders/SimpleFragmentShader.fs");

  mvp_handle = glGetUniformLocation(m_shader, "MVP");
  
  m_Model = new Model();

  int cv;
  GLfloat* v_d = m_Model->GetPositions(&cv);
  int cc;
  GLfloat* c_d = m_Model->GetColors(&cc);
  int ci;
  unsigned int* indices = m_Model->GetIndices(&ci);
  
 
  
  glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER, cv*sizeof(GLfloat), v_d, GL_DYNAMIC_DRAW);

  glGenBuffers(1, &colorbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
  glBufferData(GL_ARRAY_BUFFER, cc*sizeof(GLfloat), c_d, GL_DYNAMIC_DRAW);


   glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_CULL_FACE);

  glGenBuffers(1, &elementbuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, ci*sizeof(unsigned int), indices, GL_STATIC_DRAW);
  
  camera = new Camera();
  if(!camera)
    Exit("cannot initialize Camera");
}

void BaseGame::LoadContent()
{
  
}

void BaseGame::Update()
{
  glm::mat3 rot(1.0f);

  float a = 3.14f*(1.0f/180.0f);

  rot[0][0] = std::cos(a);
  rot[0][2] = -std::sin(a);
  rot[2][0] = std::sin(a);
  rot[2][2] = std::cos(a);
  
  glm::vec3 cd = rot*camera->GetPosition() - camera->GetPosition();

  
  
  camera->MoveCamera(cd);
}

void BaseGame::Draw()
{

  // Use our shader
    glUseProgram(m_shader);

    glm::mat4 mvp = camera->GetProjection()*camera->GetView();
    glUniformMatrix4fv(mvp_handle, 1, GL_FALSE, &mvp[0][0]);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    
    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
			  0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			  3,                  // size
			  GL_FLOAT,           // type
			  GL_FALSE,           // normalized?
			  0,                  // stride
			  (void*)0            // array buffer offset
			  );

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer(
			  1,
			  3,
			  GL_FLOAT,
			  GL_FALSE,
			  0,
			  (void*)0
			  );
    
    // Draw the triangle !
    glDrawElements(
		   GL_TRIANGLES, //mode
		   3*12, //count
		   GL_UNSIGNED_INT, //type
		   (void*)0 //element array buffer offset
		   );
    
    glDisableVertexAttribArray(0);
glDisableVertexAttribArray(1);
  
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
