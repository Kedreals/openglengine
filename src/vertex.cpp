#include "vertex.hpp"

using namespace glm;

vec3 zero3;
vec2 zero2;

Vertex::Vertex(vec3& pos, Flags f) : Vertex::Vertex(pos, zero3, zero2, zero3, f)
{
}

Vertex::Vertex(vec3& pos, vec3& otr, Flags f) : Vertex::Vertex(pos, otr, zero2, otr, f)
{
}

Vertex::Vertex(vec3& pos, vec2& uv, Flags f) : Vertex::Vertex(pos, zero3, uv, zero3, f)
{
}

Vertex::Vertex(vec3& pos, vec3& color, vec2& uv, Flags f) : Vertex::Vertex(pos, color, uv, color, f)
{
}

Vertex::Vertex(vec3& pos, vec2& uv, vec3& normal, Flags f) : Vertex::Vertex(pos, normal, uv, normal, f)
{
}

Vertex::Vertex(vec3& pos, vec3& color, vec2& uv, vec3& normal, Flags f)
{
  m_setAttrib = f;
  m_x = pos[0];
  m_y = pos[1];
  m_z = pos[2];

  if(f & Flags::Color)
    {
      m_r = color[0];
      m_g = color[1];
      m_b = color[2];
    }
  if(f & Flags::UV)
    {
      m_u = uv[0];
      m_v = uv[1];
    }
  if(f & Flags::Normal)
    {
      m_nx = normal[0];
      m_ny = normal[1];
      m_nz = normal[2];
    }
}

Vertex::Vertex(const Vertex& v) : m_setAttrib(v.m_setAttrib), m_x(v.m_x), m_y(v.m_y), m_z(v.m_z), m_r(v.m_r), m_g(v.m_g), m_b(v.m_b), m_u(v.m_u), m_v(v.m_v), m_nx(v.m_nx), m_ny(v.m_ny), m_nz(v.m_nz)
{
}

Vertex::~Vertex()
{
}

bool Vertex::IsSet(Vertex::Flags f) const
{
  if(f == Flags::Position)
    return true;

  return (m_setAttrib & f) == f;
}

void Vertex::GetSetAttribArray(bool* resArray) const
{
  resArray[0] = IsSet(Flags::Position);
  resArray[1] = IsSet(Flags::Color);
  resArray[2] = IsSet(Flags::UV);
  resArray[3] = IsSet(Flags::Normal);
}

const void* GetPointerTo(Vertex::Flags f)
{
  switch(f)
    {
    case Vertex::Flags::Position:
      return (void*)sizeof(Vertex::Flags);
    case Vertex::Flags::Color:
      return (void*)(sizeof(Vertex::Flags)+3*sizeof(float));
    case Vertex::Flags::UV:
      return (void*)(sizeof(Vertex::Flags)+6*sizeof(float));
    case Vertex::Flags::Normal:
      return (void*)(sizeof(Vertex::Flags)+8*sizeof(float));
    default:
      return nullptr;
    }
}
	
