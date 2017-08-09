// Include standard headers
#include <stdio.h>
#include <stdlib.h>

#include <iostream>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

#include "shader.hpp"


std::ostream& operator <<(std::ostream& lhs, const glm::mat4& rhs)
{
  return lhs
    << rhs[0][0] << ", " << rhs[0][1] << ", " << rhs[0][2] << ", " << rhs[0][3] << "\n"
    << rhs[1][0] << ", " << rhs[1][1] << ", " << rhs[1][2] << ", " << rhs[0][3] << "\n"
    << rhs[2][0] << ", " << rhs[2][1] << ", " << rhs[2][2] << ", " << rhs[2][3] << "\n"
    << rhs[3][0] << ", " << rhs[3][1] << ", " << rhs[3][2] << ", " << rhs[3][3] << "\n";
}

std::ostream& operator <<(std::ostream& lhs, const glm::vec3& rhs)
{
  return lhs << rhs.x << ", " << rhs.y << ", " << rhs.z << "\n";
}



glm::vec3 Update(glm::vec3& cam_pos)
{
  float deg = glm::radians(0.1f);
  
  glm::mat4 rot;
  rot[0][0] = cos(deg);
  rot[0][2] = -sin(deg);
  rot[2][0] = sin(deg);
  rot[2][2] = cos(deg);
  rot[1][1] = 1.0f;
  rot[3][3] = 1.0f;
  
  vec4 r = rot*vec4(cam_pos,1.0f);

  cam_pos = vec3((float)r.x, (float)r.y, (float)r.z);
  
  return cam_pos;
}

int main( void )
{
  // Initialise GLFW
  if( !glfwInit() )
    {
      fprintf( stderr, "Failed to initialize GLFW\n" );
      getchar();
      return -1;
    }
  
  glfwWindowHint(GLFW_SAMPLES, 4); // sample 4 times
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //using opengl 3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // .3
  //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //switch to new opengl

  int width = 1024;
  int height = 768;
  
  // Open a window and create its OpenGL context
  window = glfwCreateWindow( width, height, "Engine", NULL, NULL);
  if( window == NULL ){
    fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
    getchar();
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  
  // Initialize GLEW
  glewExperimental = true; //needed for core profile
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW\n");
    getchar();
    glfwTerminate();
    return -1;
  }
  
  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
  
  // black background
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  
  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);
  
  //Create and compile our GLSL program from the shaders
  GLuint programID = LoadShaders("../shaders/SimpleVertexShader.vs", "../shaders/SimpleFragmentShader.fs");

  static const GLfloat g_vertex_buffer_data[] = {
    -1.0f,-1.0f, 1.0f,
     1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
     1.0f,-1.0f,-1.0f,

    -1.0f, 1.0f,-1.0f,
     1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
     1.0f, 1.0f, 1.0f
  };

  static const GLfloat g_color_buffer_data[] = {
    0.0f,0.0f, 1.0f,
     1.0f,0.0f, 1.0f,
    0.0f,0.0f,0.0f,
     1.0f,0.0f,0.0f,

    0.0f, 1.0f,0.0f,
     1.0f, 1.0f,0.0f,
    0.0f, 1.0f, 1.0f,
     1.0f, 1.0f, 1.0f
  };
  
  
  GLuint vertexbuffer;
  glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_DYNAMIC_DRAW);

  GLuint colorbuffer;
  glGenBuffers(1, &colorbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_DYNAMIC_DRAW);

  GLuint mvp_handle = glGetUniformLocation(programID, "MVP");
  
  glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

  vec3 cam_pos(-4.0f,3.0f,-3.0f);

  glm::mat4 View = glm::lookAt(cam_pos,
			       glm::vec3(0,0,0),
			       glm::vec3(0,1,0)
			       );
  glm::mat4 Model = glm::mat4(1.0f);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_CULL_FACE);


  unsigned int indices[36];

  //fill indices
  indices[0] = 0;
  indices[1] = 2;
  indices[2] = 1;
  
  indices[3] = 1;
  indices[4] = 2;
  indices[5] = 3;
  
  indices[6] = 2;
  indices[7] = 4;
  indices[8] = 3;
  
  indices[9] = 3;
  indices[10] = 4;
  indices[11] = 5;
  
  indices[12] = 0;
  indices[13] = 4;
  indices[14] = 2;
  
  indices[15] = 0;
  indices[16] = 6;
  indices[17] = 4;
  
  indices[18] = 1;
  indices[19] = 3;
  indices[20] = 7;
  
  indices[21] = 3;
  indices[22] = 5;
  indices[23] = 7;
  
  indices[24] = 0;
  indices[25] = 1;
  indices[26] = 7;
  
  indices[27] = 0;
  indices[28] = 7;
  indices[29] = 6;
  
  indices[30] = 6;
  indices[31] = 7;
  indices[32] = 5;
  
  indices[33] = 6;
  indices[34] = 5;
  indices[35] = 4;
    
  GLuint elementbuffer;
  glGenBuffers(1, &elementbuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36*sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
  
  do{

    cam_pos = Update(cam_pos);
    View = glm::lookAt(cam_pos,
		       glm::vec3(0,0,0),
		       glm::vec3(0,1,0)
		       );

    glm::mat4 mvp = Projection*View*Model;
    
    // Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // Use our shader
    glUseProgram(programID);

    
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
    
    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
    
  } // Check if the ESC key was pressed or the window was closed
  while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
	 !glfwWindowShouldClose(window));

  
  //Cleanup VBO
  glDeleteBuffers(1, &vertexbuffer);
  glDeleteVertexArrays(1, &VertexArrayID);
  glDeleteProgram(programID);
  
  
  // Close OpenGL window and terminate GLFW
  glfwTerminate();
  
  return 0;
}

