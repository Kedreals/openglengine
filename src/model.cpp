#include "model.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include <glm/glm.hpp>
#include <cstring>
#include "camera.hpp"
#include "debug.hpp"

using namespace glm;

Model::Model(const std::string& file) : m_position(0,0,0), m_orientation(1, 0,0,0), m_scaling(1,1,1)
{
  glGenVertexArrays(1, &m_vertexArrayID);
  glBindVertexArray(m_vertexArrayID);
  
  if(file == "")
    {
      std::clog << "initializing model with default values\n";
      
      m_vertexPositions = std::vector<glm::vec3>(8);
      for(int i = 0; i < 8; ++i)
	{
	  float x = i%2;
	  float y = i/4;
	  float z = (i/2)%2;
	  
	  m_vertexPositions.push_back(glm::vec3(x,y,z));
	  m_vertexPositions[i] = m_vertexPositions[i]*2.0f + glm::vec3(-1,-1,-1);
	}
      m_vertexColors = std::vector<glm::vec3>(8);
      for(int i = 0; i < 8; ++i)
	{
	  m_vertexColors[i] = m_vertexPositions[i]*0.5f + glm::vec3(0.5f, 0.5f, 0.5f);
	}

      m_indices = std::vector<unsigned int>(36);
      m_indices[0] = 0;
      m_indices[1] = 2;
      m_indices[2] = 1;
      
      m_indices[3] = 1;
      m_indices[4] = 2;
      m_indices[5] = 3;
      
      m_indices[6] = 2;
      m_indices[7] = 6;
      m_indices[8] = 3;
      
      m_indices[9] = 3;
      m_indices[10] = 6;
      m_indices[11] = 7;
      
      m_indices[12] = 0;
      m_indices[13] = 6;
      m_indices[14] = 2;
      
      m_indices[15] = 0;
      m_indices[16] = 4;
      m_indices[17] = 6;
      
      m_indices[18] = 1;
      m_indices[19] = 3;
      m_indices[20] = 5;
  
      m_indices[21] = 3;
      m_indices[22] = 7;
      m_indices[23] = 5;
      
      m_indices[24] = 0;
      m_indices[25] = 1;
      m_indices[26] = 5;
      
      m_indices[27] = 0;
      m_indices[28] = 5;
      m_indices[29] = 4;
      
      m_indices[30] = 4;
      m_indices[31] = 5;
      m_indices[32] = 7;
      
      m_indices[33] = 4;
      m_indices[34] = 7;
      m_indices[35] = 6;
    }
  else
    {
      return;
    }

  GLfloat g_vertex_buffer_data[m_vertexPositions.size()*3];
  for(size_t i = 0; i < m_vertexPositions.size(); ++i)
    {
      g_vertex_buffer_data[i*3+0] = m_vertexPositions[i][0];
      g_vertex_buffer_data[i*3+1] = m_vertexPositions[i][1];
      g_vertex_buffer_data[i*3+2] = m_vertexPositions[i][2];
    }

  GLfloat g_color_buffer_data[m_vertexColors.size()*3];
  for(size_t i = 0; i<m_vertexColors.size(); ++i)
    {
      g_color_buffer_data[i*3+0] = m_vertexColors[i][0];
      g_color_buffer_data[i*3+1] = m_vertexColors[i][1];
      g_color_buffer_data[i*3+2] = m_vertexColors[i][2];
    }
  
  glGenBuffers(1,&m_vertexBuffer);
      glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
      glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_DYNAMIC_DRAW);

      glGenBuffers(1,&m_colorBuffer);
      glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
      glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_DYNAMIC_DRAW);

      glGenBuffers(1, &m_indexBuffer);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*m_indices.size(), m_indices.data(), GL_STATIC_DRAW);
}

Model::Model(const Model& other) : m_position(other.m_position), m_orientation(other.m_orientation), m_scaling(other.m_scaling), m_vertexPositions(other.m_vertexPositions.size()), m_vertexColors(other.m_vertexColors.size()), m_indices(other.m_indices.size())
{
  std::memcpy(m_vertexPositions.data(), other.m_vertexPositions.data(), other.m_vertexPositions.size()*sizeof(glm::vec3));
  std::memcpy(m_vertexColors.data(), other.m_vertexColors.data(), other.m_vertexColors.size()*sizeof(glm::vec3));
  std::memcpy(m_indices.data(), other.m_indices.data(), other.m_indices.size()*sizeof(int));
}

Model::Model(Model& other) :m_position(other.m_position), m_orientation(other.m_orientation), m_scaling(other.m_scaling), m_vertexPositions(other.m_vertexPositions.size()), m_vertexColors(other.m_vertexColors.size()), m_indices(other.m_indices.size())
{
  std::memcpy(m_vertexPositions.data(), other.m_vertexPositions.data(), other.m_vertexPositions.size()*sizeof(glm::vec3));
  std::memcpy(m_vertexColors.data(), other.m_vertexColors.data(), other.m_vertexColors.size()*sizeof(glm::vec3));
  std::memcpy(m_indices.data(), other.m_indices.data(), other.m_indices.size()*sizeof(int));
}

Model::~Model()
{
  glDeleteBuffers(1, &m_vertexBuffer);
  glDeleteVertexArrays(1, &m_vertexArrayID);
}

void Model::Translate(const glm::vec3& translation)
{
  m_position += translation;
}

void Model::Rotate(const glm::vec3& eulerangles)
{
  glm::vec3 radians = ((float)(M_PI / 180.0f))*eulerangles;

  glm::quat rot(radians);
  Rotate(rot);
}

void Model::Rotate(const glm::quat& rotation)
{
  m_orientation = rotation*m_orientation;
}

void Model::Scale(const glm::vec3& scaling)
{
  m_scaling += scaling;
}

void Model::SetPosition(const glm::vec3& position)
{
  m_position = position;
}

void Model::SetOrientation(const glm::vec3& eulerangles)
{
  SetOrientation(glm::quat(((float)(M_PI / 180.0f))*eulerangles));
}

void Model::SetOrientation(const glm::quat& orientation)
{
  m_orientation = orientation;
}

void Model::SetScale(const glm::vec3& scale)
{
  m_scaling = scale;
}

const glm::vec3& Model::GetPosition() const
{
  return m_position;
}

const glm::quat& Model::GetOrientation() const
{
  return m_orientation;
}

const glm::vec3& Model::GetScaling() const
{
  return m_scaling;
}

glm::mat4 Model::GetWorldMatrix() const
{
  glm::mat4 res;

  res = translate(res, m_position) * mat4_cast(m_orientation) * scale(res, m_scaling)*res;

  return res;
}

void Model::Draw(const Camera& cam, GLuint progID, GLuint mvp_handle) const
{
  glUseProgram(progID);
  
  glm::mat4 mvp = cam.GetProjection()*cam.GetView()*GetWorldMatrix();

  glUniformMatrix4fv(mvp_handle, 1, GL_FALSE, &mvp[0][0]);
    
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);

  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

  glDrawElements(GL_TRIANGLES, 3*12, GL_UNSIGNED_INT, nullptr);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}

GLfloat* Model::GetPositions(int* count) const
{
  *count = m_vertexPositions.size()*3;
  GLfloat* res = (GLfloat*)malloc(sizeof(GLfloat)*(*count));
  for(size_t i = 0; i < m_vertexPositions.size(); ++i)
    {
      res[i*3+0] = m_vertexPositions[i][0];
      res[i*3+1] = m_vertexPositions[i][1];
      res[i*3+2] = m_vertexPositions[i][2];
    }
  return res;
}

GLfloat* Model::GetColors(int* count) const
{
  *count = m_vertexColors.size()*3;
  GLfloat* res = (GLfloat*)malloc(sizeof(GLfloat)*(*count));
  for(size_t i = 0; i < m_vertexColors.size(); ++i)
    {
      res[i*3+0] = m_vertexColors[i][0];
      res[i*3+1] = m_vertexColors[i][1];
      res[i*3+2] = m_vertexColors[i][2];
    }
  return res;
}

unsigned int* Model::GetIndices(int* count) const
{
  *count = m_indices.size();
  unsigned int* res = (unsigned int*)malloc(sizeof(unsigned int)*(*count));
  for(size_t i = 0; i < m_indices.size(); ++i)
    {
      res[i] = m_indices[i];
    }
  return res;
}
