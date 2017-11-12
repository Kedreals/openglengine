#include "vertexBuffer.hpp"

VertexBuffer::VertexBuffer() : m_format(VertexFormat::None), m_vertices()
{
}

VertexBuffer::~VertexBuffer()
{
}

void VertexBuffer::push_back(Vertex v, VertexFormat format)
{
  if(m_format == VertexFormat::None)
    m_format = format;

  if(m_format != format)
    {
      std::cerr << "Trying to add Vertex with different format than all the other in the Buffer\n";
      throw 1;
    }

  m_vertices.push_back(v);
}

size_t VertexBuffer::size()
{
  return m_vertices.size();
}

/*const Vertex& operator[](int index)
{
  return m_vertices[index];
  }*/

Vertex& VertexBuffer::operator[](int index)
{
  return m_vertices[index];
}

void VertexBuffer::GetInfoForAttrib(size_t i, AttribInfo* res)
{
  res->IsSet = false;
  res->size = 0;
  res->Normalized = false;
  res->pointer = nullptr;

  switch(i)
    {
    case 0:
      res->IsSet = (m_format & VertexFormat::Position) == VertexFormat::Position;
      res->size = 3;
      res->pointer = nullptr;
      break;
    case 1:
      res->IsSet = (m_format & VertexFormat::PositionColor) == VertexFormat::PositionColor;
      res->size = 3;
      res->Normalized = true;
      res->pointer = (void*)(3*sizeof(float));
      break;
    case 2:
      res->IsSet = (m_format & VertexFormat::PositionUV) == VertexFormat::PositionUV;
      res->size=2;
      res->pointer = (void*)(6*sizeof(float));
      break;
    case 3:
      res->IsSet = (m_format & VertexFormat::PositionNormal) == VertexFormat::PositionNormal;
      res->size =3;
      res->pointer = (void*)(8*sizeof(float));
      break;
    default:
      break;
    }
}
