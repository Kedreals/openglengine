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

Vertex::Vertex(const Vertex& v) : m_x(v.m_x), m_y(v.m_y), m_z(v.m_z), m_r(v.m_r), m_g(v.m_g), m_b(v.m_b), m_u(v.m_u), m_v(v.m_v), m_nx(v.m_nx), m_ny(v.m_ny), m_nz(v.m_nz)
{
}

Vertex::~Vertex()
{
}

float Vertex::operator[](int index) const
{
  switch(index){
  case 0: return m_x;
  case 1: return m_y;
  case 2: return m_z;
  case 3: return m_r;
  case 4: return m_g;
  case 5: return m_b;
  case 6: return m_u;
  case 7: return m_v;
  case 8: return m_nx;
  case 9: return m_ny;
  case 10: return m_nz;
  default: return 0;
  }
}
	
/*std::ostream& operator <<(std::ostream& lhs, const Vertex& rhs)
{
  lhs << "Position (" << rhs[0] << ", " << rhs[1] << ", " << rhs[2] << ")";
  if(rhs.IsSet(Vertex::Flags::Color))
    {
      lhs << ";  Color (" << rhs[3] << ", " << rhs[4] << ", " << rhs[5] << ")";
    }
  if(rhs.IsSet(Vertex::Flags::UV))
    {
      lhs << ";  UV (" << rhs[6] << ", " << rhs[7] << ")";
    }
  if(rhs.IsSet(Vertex::Flags::Normal))
    {
      lhs << ";  Normal (" << rhs[8] << ", " << rhs[9] << ", " << rhs[10] << ")";
    }
  return lhs << "\n";
  }*/
