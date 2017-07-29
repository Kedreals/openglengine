#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include "math_3d.hpp"

GLuint VBO;
/**\todo: work through opengl tutorials
 */
void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_POINTS, 0, 1);

    glDisableVertexAttribArray(0);
    
    glutSwapBuffers();
}

void InitializeGlutCallbacks()
{
    glutDisplayFunc(RenderSceneCB);
}

void CreateVertexBuffer()
{
  Vec3 Vertices[1];
  Vertices[0] = Vec3(0, 0, 0);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tutorial 01");

    InitializeGlutCallbacks();

    GLenum res = glewInit();
    if(res != GLEW_OK)
      {
	std::cerr << "ERROR: " << glewGetErrorString(res) << std::endl;
	return 1;
      }
    

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    CreateVertexBuffer();
    
    glutMainLoop();
    
    return 0;
}
