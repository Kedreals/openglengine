#ifndef VEC3_H
#define VEC3_H

/** \brief simple 3d Vector
 */
class Vec3
{
 public:
  float X, Y, Z;
  
 public:

  Vec3();
  Vec3(float x, float y, float z);
  Vec3(const Vec3&);
  Vec3(Vec3&);
  ~Vec3();

  Vec3 operator +(const Vec3& rhs) const;
  Vec3& operator +=(const Vec3& rhs);
  Vec3 operator -(const Vec3& rhs) const;
  Vec3& operator -=(const Vec3& rhs);

  Vec3 operator *(float rhs) const;
  Vec3& operator *=(float rhs);
  Vec3 operator /(float rhs) const;
  Vec3& operator /=(float rhs);

  float& operator [](unsigned int index);
  const float& operator [](unsigned int index) const;

  float dot(const Vec3& rhs) const;
  Vec3 cross(const Vec3& rhs) const;
  float length() const;
  float sqrlength() const;
};

Vec3 operator*(float lhs, const Vec3& rhs);

#endif //VEC3_H
