#include "model.hpp"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "modelLoader.hpp"


Model::Model(const char* f):m_orientation(glm::vec3(0,0,0)), m_World(1.0f), m_initialized(false), m_vertecies()
{
  std::string file = f;

  if(file == "")
    {
      unsigned char data[3];
      data[0] = 128;
      data[1] = 128;
      data[2] = 128;
      
      glGenTextures(1, &m_texture);
      glBindTexture(GL_TEXTURE_2D, m_texture);

      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);

      
      for(size_t i = 0; i < 8; ++i)
	{
	  bool x(i/4 < 1), y((i%4)/2 < 1), z(i%2 < 1);
	  
	  glm::vec3 pos((x)?(-1):(1), (y)?(-1):(1), (z)?(-1):(1));
	  glm::vec3 col((x)?( 0):(1), (y)?( 0):(1), (z)?( 0):(1));
	  glm::vec2 tex((x)?( 0):(1), (y)?( 0):(1));
	  
	  Vertex v(pos, col, tex, Vertex::Flags::ColorUV);
      
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
      Loading::Load(this, file);
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

void Model::Rotate(const glm::vec3& eulerAngles)
{
  glm::quat rot(eulerAngles);
  Rotate(rot);
}

void Model::Rotate(const glm::quat& rotation)
{
  m_orientation=rotation*m_orientation;
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
  glBindTexture(GL_TEXTURE_2D, m_texture);
  AttribInfo info[4];
  for(size_t i = 0; i < 4; ++i)
    {
      m_vertecies.GetInfoForAttrib(i,&info[i]);
      if(info[i].IsSet)
	{
	  glEnableVertexAttribArray(i);
	  glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	  glVertexAttribPointer(
				i,
				info[i].size,
				GL_FLOAT,
				info[i].Normalized,
				sizeof(Vertex),
				info[i].pointer);
	}
    }
  
  glDrawElements(
		 GL_TRIANGLES,
		 m_indices.size(),
		 GL_UNSIGNED_INT,
		 (void*)0);

  for(size_t i = 0; i < 4; ++i)
    {
      if(info[i].IsSet)
	glDisableVertexAttribArray(i);
    }
}
