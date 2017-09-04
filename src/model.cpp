#include "model.hpp"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <string>


Model::Model(const char* f):m_orientation(glm::vec3(0,0,0)), m_World(1.0f), m_initialized(false), m_vertecies()
{
  std::string file = f;

  if(file == "")
    {
  
      for(size_t i = 0; i < 8; ++i)
	{
	  bool x(i/4 < 1), y((i%4)/2 < 1), z(i%2 < 1);
	  
	  glm::vec3 pos((x)?(-1):(1), (y)?(-1):(1), (z)?(-1):(1));
	  glm::vec3 col((x)?( 0):(1), (y)?( 0):(1), (z)?( 0):(1));
	  
	  Vertex v(pos, col, Vertex::Flags::Color);
      
	  m_vertecies.push_back(v);
	}

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

      for(size_t i = 0; i < 36; ++i)
	m_indices.push_back(indices[i]);
    }
  else
    {
      
    }
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
  
  glGenBuffers(1, &m_vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*m_vertecies.size(), &m_vertecies[0], GL_DYNAMIC_DRAW);

  glGenBuffers(1, &m_indexBuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*m_indices.size(), &m_indices[0], GL_STATIC_DRAW);

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
  glm::mat4 mvp = vp*m_World*glm::scale(glm::mat4(1.0f), glm::vec3(m_Scale, m_Scale, m_Scale))*glm::mat4_cast(m_orientation);

    glUniformMatrix4fv(mvp_handle, 1, GL_FALSE, &mvp[0][0]);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);

  bool SetAttrib[4];
  m_vertecies[0].GetSetAttribArray(SetAttrib);

  for(size_t i = 0; i < 4; ++i)
    {
      if(SetAttrib[i])
	{
	  glEnableVertexAttribArray(i);
	  glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	  glVertexAttribPointer(
				i,
				(i!=2)?3:2,
				GL_FLOAT,
				(i==1)?GL_TRUE:GL_FALSE,
				sizeof(Vertex),
				GetPointerTo(i==0?Vertex::Flags::Position:(Vertex::Flags)(Vertex::Flags::Color << (i-1))));
	}
    }
  
  glDrawElements(
		 GL_TRIANGLES,
		 36,
		 GL_UNSIGNED_INT,
		 (void*)0);

  for(size_t i = 0; i < 4; ++i)
    {
      if(SetAttrib[i])
	glDisableVertexAttribArray(i);
    }
}
