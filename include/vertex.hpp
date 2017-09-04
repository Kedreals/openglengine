#ifndef _VERTEX_HPP_
#define _VERTEX_HPP_

#include <glm/glm.hpp>

/** \todo wrapper class for a vertex container that holds the meta information which is now saved inside the vertices
    \brief simple class that contains all informations of one vertex
    
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

  /** \brief returns if the given flags are set
   */
  bool IsSet(Flags f) const;

  /** \brief sets \a resArray so that the values corralate with the set properties

      resArray should allways have space for atleast 4 bool values.
      resArray[0] corralates to position
      resArray[1] corralates to color
      resArray[2] corralates to uv
      resArray[3] corralates to normal
   */
  void GetSetAttribArray(bool* resArray) const;
private:
  Flags m_setAttrib;
  float m_x, m_y, m_z, m_r, m_g, m_b, m_u, m_v, m_nx, m_ny, m_nz;
};

/** \brief gets the offset for the given flag

    do not use mixed flags. Only use one of the following flags
    Position, Color, UV, Normal
 */
const void* GetPointerTo(Vertex::Flags f);

#endif //_VERTEX_HPP_
