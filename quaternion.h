#ifndef QUATERNION_H
#define QUATERNION_H

#include <QVector3D>
#include <QMatrix3x3>

//class Vec3
//{
//public:
//  Vec3(float x, float y, float z);

//  float x() const;
//  float y() const;
//  float z() const;

//  static float dot(const Vec3 &a, const Vec3 &b);
//  static Vec3 cross(const Vec3 &a, const Vec3 &b);
//  friend inline Vec3 operator+ (const Vec3 &a, const Vec3 &b);
//  friend inline Vec3 operator* (float scalar, const Vec3 &a);

//private:
//  float _x, _y, _z;
//};

typedef QVector3D Vec3;
typedef QMatrix3x3 Mat3;

class Quaternion
{
public:
  Quaternion();
  Quaternion(float w, float x, float y, float z);
  Quaternion(float scalar, const Vec3 &vec);

  float getW() const;
  float getX() const;
  float getY() const;
  float getZ() const;

  Vec3 vec() const;
  Mat3 toRotMat();
  static Quaternion fromAxisAndAngle(Vec3 &axis, float angle);
  static Quaternion fromEulerAngles(float alpha, float beta, float gamma);
  Vec3 toEulerAngles();

  friend inline Quaternion operator* (const Quaternion &a, const Quaternion &b);
  friend inline Quaternion operator+ (const Quaternion &a, const Quaternion &b);
private:
  float w, x, y, z;
};

Vec3 fromRotMatToEulerAngles(Mat3 M);
#endif // QUATERNION_H
