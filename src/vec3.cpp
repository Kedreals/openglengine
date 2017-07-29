#include "vec3.hpp"
#include <cmath>

Vec3::Vec3() : X(0.0), Y(0.0), Z(0.0) {}

Vec3::Vec3(float x, float y, float z) : X(x), Y(y), Z(z) {}

Vec3::Vec3(const Vec3& other) : X(other.X), Y(other.Y), Z(other.Z) {}

Vec3::Vec3(Vec3& other) : X(other.X), Y(other.Y), Z(other.Z) {}

Vec3::~Vec3()
{
  X = Y = Z = 0.0f;
}

Vec3 Vec3::operator +(const Vec3& lhs) const
{
  return Vec3(X + lhs.X, Y + lhs.Y, Z + lhs.Z);
}

Vec3& Vec3::operator +=(const Vec3& rhs)
{
  X += rhs.X;
  Y += rhs.Y;
  Z += rhs.Z;

  return *this;
}

Vec3 Vec3::operator -(const Vec3& rhs) const
{
  return Vec3(X-rhs.X, Y-rhs.Y, Z-rhs.Z);
}

Vec3& Vec3::operator -=(const Vec3& rhs)
{
  X -= rhs.X;
  Y -= rhs.Y;
  Z -= rhs.Z;

  return *this;
}

Vec3 Vec3::operator *(float rhs) const
{
  return Vec3(X*rhs, Y*rhs, Z*rhs);
}

Vec3& Vec3::operator *=(float rhs)
{
  X *= rhs;
  Y *= rhs;
  Z *= rhs;

  return *this;
}

Vec3 Vec3::operator /(float rhs) const
{
  return Vec3(X/rhs, Y/rhs, Z/rhs);
}

Vec3& Vec3::operator /=(float rhs)
{
  X /= rhs;
  Y /= rhs;
  Z /= rhs;

  return *this;
}

float& Vec3::operator [](unsigned int index)
{
  int t = index % 3;
  float* value = (float*)this;
  return value[t];
}

const float& Vec3::operator [](unsigned int index) const
{
  int t = index % 3;
  float* value = (float*)this;
  return value[t];
}

float Vec3::dot(const Vec3& rhs) const
{
  return X*rhs.X + Y*rhs.Y + Z*rhs.Z;
}

Vec3 Vec3::cross(const Vec3& rhs) const
{
  return Vec3(Y*rhs.Z-Z*rhs.Y, Z*rhs.X-X*rhs.Z, X*rhs.Y-Y*rhs.X);
}

float Vec3::sqrlength() const
{
  return dot(*this);
}

float Vec3::length() const
{
  return std::sqrt(dot(*this));
}

Vec3 operator *(float lhs, const Vec3& rhs)
{
  return rhs*lhs;
}
