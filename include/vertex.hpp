#ifndef _VERTEX_HPP_
#define _VERTEX_HPP_

#include <glm/glm.hpp>
#include <iostream>

/** \brief simple class that contains all informations of one vertex
    
    contains information about the position, color, uv and normal of an vertex
    as well as the meta information which of these are actualy set.
 */
class Vertex
{
public:
  /** \brief an enum that holds the Flags for which properties can be set
   */
  typedef enum Flags : unsigned int
    {

      Position = 0b0,
	Color = 0b1,
	UV = 0b10,
	ColorUV = 0b11,
	Normal = 0b100,
	UVNormal = 0b110,
	ColorUVNormal = 0b111
	
    } Flags;

  /** \brief ctor that sets only the position
   */
  Vertex(glm::vec3& position, Flags f = Flags::Position);
  /** \brief ctor that sets position and color/normal depending on the flag
   */
  Vertex(glm::vec3& position, glm::vec3& otr, Flags f = Flags::Color);
  /** \brief ctor that sets position and uv
   */
  Vertex(glm::vec3& position, glm::vec2& uv, Flags f = Flags::UV);

  /** \brief ctor that sets position, color/normal und uv depending on the flag
   */
  Vertex(glm::vec3& position, glm::vec3& color, glm::vec2& uv, Flags f = Flags::ColorUV);
  /** \brief ctor that sets position, uv and color/normal depending on the flag
   */
  Vertex(glm::vec3& position, glm::vec2& uv, glm::vec3& normal, Flags f = Flags::UVNormal);
  /** \brief ctor that sets position and any of the other properties depending on the flag
   */
  Vertex(glm::vec3& position, glm::vec3& color, glm::vec2& uv, glm::vec3& normal, Flags f = Flags::ColorUVNormal);

  /** \brief copy ctor
   */
  Vertex(const Vertex&);
  /** \brief default dtor
   */
  ~Vertex();

  
    
  float operator[](int index) const;
private:
  float m_x, m_y, m_z, m_r, m_g, m_b, m_u, m_v, m_nx, m_ny, m_nz;
};

//std::ostream& operator <<(std::ostream&, const Vertex&);

#endif //_VERTEX_HPP_
