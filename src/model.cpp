#include "model.hpp"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>


Model::Model():m_World(1.0f), m_initialized(false)
{
}

Model::~Model()
{
  if(!m_initialized)
    return;

  glDeleteBuffers(1, &m_vertexBuffer);
  glDeleteBuffers(1, &m_colorBuffer);
  glDeleteBuffers(1, &m_indexBuffer);

  glDeleteVertexArrays(1, &m_vertexArrayID);
}

bool Model::Initialize()
{
  glGenVertexArrays(1, &m_vertexArrayID);
  glBindVertexArray(m_vertexArrayID);

  GLfloat pos[8*3] =
    {
      -1,-1,-1,
      -1,-1, 1,
      -1, 1,-1,
      -1, 1, 1,
       1,-1,-1,
       1,-1, 1,
       1, 1,-1,
       1, 1, 1
    };
  
  glGenBuffers(1, &m_vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_DYNAMIC_DRAW);

  GLfloat col[8*3] =
    {
      0,0,0,
      0,0,1,
      0,1,0,
      0,1,1,
      1,0,0,
      1,0,1,
      1,1,0,
      1,1,1
    };

  glGenBuffers(1,&m_colorBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(col), col, GL_DYNAMIC_DRAW);

  unsigned int indices[36] =
    {
      0,1,3,
      0,3,2,

      1,0,4,
      1,4,5,

      0,2,6,
      0,6,4,

      4,6,5,
      6,7,5,

      5,7,3,
      5,3,1,

      7,6,2,
      7,2,3
    };

  glGenBuffers(1, &m_indexBuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  m_initialized = true;
  return m_initialized;
}

void Model::Translate(const glm::vec3& translation)
{
  m_World = glm::translate(glm::mat4(1.0f), translation)*m_World;
}

void Model::Scale(float scaling)
{
  m_Scale = scaling;
}

void Model::Draw(const glm::mat4& vp, GLuint shader, GLuint mvp_handle)
{
  if(!m_initialized)
    {
      std::cerr << "Model was not initialized\n";
      return;
    }
  
  glBindVertexArray(m_vertexArrayID);

  glUseProgram(shader);
  glm::mat4 mvp = vp*m_World*glm::scale(glm::mat4(1.0f), glm::vec3(m_Scale, m_Scale, m_Scale));

    glUniformMatrix4fv(mvp_handle, 1, GL_FALSE, &mvp[0][0]);

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
}
