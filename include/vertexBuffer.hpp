#ifndef _VERTEX_BUFFER_HPP_
#define _VERTEX_BUFFER_HPP_

#include "vertex.hpp"
#include <vector>

enum VertexFormat
  {
    None = -1,
    Position = 0b0,
    PositionColor = 0b1,
    PositionUV = 0b10,
    PositionNormal = 0b100,
    PositionColorUV = 0b11,
    PositionColorNormal = 0b101,
    PositionColorUVNormal = 0b111
  };

struct AttribInfo
{
  bool IsSet;
  int size;
  bool Normalized;
  void* pointer;
};

class VertexBuffer
{
public:
  VertexBuffer();
  VertexBuffer(const VertexBuffer&) = delete;
  ~VertexBuffer();

  void push_back(Vertex v, VertexFormat format = VertexFormat::PositionColor);
  size_t size();
  //const Vertex& operator[](int index);
  Vertex& operator[](int index);

  void GetInfoForAttrib(size_t i, AttribInfo* res);
  
private:
  VertexFormat m_format;
  std::vector<Vertex> m_vertices;
};

#endif //_VERTEX_BUFFER_HPP_
