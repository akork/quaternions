#include "quaternion.h"
#include "math.h"
#include <QDebug>

Quaternion::Quaternion() :
  w(1), x(0), y(0), z(0)
{ }

Quaternion::Quaternion(float w, float x, float y, float z) :
  w(w), x(x), y(y), z(z)
{ }

Quaternion::Quaternion(float scalar, const Vec3 &vec) :
  w(scalar), x(vec.x()), y(vec.y()), z(vec.z())
{ }

float Quaternion::getW() const
{
  return w;
}

float Quaternion::getX() const
{
  return x;
}

float Quaternion::getY() const
{
  return y;
}

float Quaternion::getZ() const
{
  return z;
}

Vec3 Quaternion::vec() const
{
  return Vec3(x, y, z);
}

Mat3 Quaternion::toRotMat()
{
  Mat3 mat;
  mat.setToIdentity();
  mat(0, 0) = 1 - 2*y*y - 2*z*z;
  mat(1, 0) = 2*x*y + 2*z*w;
  mat(2, 0) = 2*x*z - 2*y*w;
  mat(0, 1) = 2*x*y - 2*z*w;
  mat(1, 1) = 1 - 2*x*x - 2*z*z;
  mat(2, 1) = 2*y*z + 2*x*w;
  mat(0, 2) = 2*x*z+2*y*w;
  mat(1, 2) = 2*y*z - 2*x*w;
  mat(2, 2) = 1 - 2*x*x - 2*y*y;

  return mat;
}

Quaternion Quaternion::fromAxisAndAngle(Vec3 &axis, float angle)
{
  return Quaternion(
        cos(angle/2),
        sin(angle/2)*axis
        );
}

Quaternion Quaternion::fromEulerAngles(float alpha, float beta, float gamma)
{
  Vec3 alphaAxis = {0, 0, 1};
  Vec3 betaAxis = {1, 0, 0};
  Vec3 gammaAxis = {0, 0, 1};

  return
      Quaternion::fromAxisAndAngle(alphaAxis, alpha) *
      Quaternion::fromAxisAndAngle(betaAxis, beta) *
      Quaternion::fromAxisAndAngle(gammaAxis, gamma);
}

Vec3 Quaternion::toEulerAngles()
{
  return fromRotMatToEulerAngles(toRotMat());
}

Vec3 fromRotMatToEulerAngles(Mat3 M)
{
  Vec3 angles;

  auto eps = std::numeric_limits<float>::epsilon();

    float sy = sqrt(M(2, 0)*M(2, 0) + M(2, 1)*M(2, 1));
    if (sy > 16*eps) {
        angles[0] = atan2(M(2, 0), M(2, 1));
        angles[1]  = atan2(sy, M(2, 2));
        angles[2] = atan2(M(0, 2), -M(1, 2));
    } else {
        angles[0] = atan2(-M(0, 1), M(0, 0));
        angles[1]  = atan2(sy, M(2, 2));
        angles[2] = 0;
    }

    return angles * 180 / M_PI;
}

inline Quaternion operator*(const Quaternion &a, const Quaternion &b)
{
  return Quaternion(
        a.w * b.w - Vec3::dotProduct(a.vec(), b.vec()),
        a.w * b.vec() + b.w * a.vec() + Vec3::crossProduct(a.vec(), b.vec())
        );
}

inline Quaternion operator+(const Quaternion &a, const Quaternion &b)
{
  return Quaternion(
        a.w + b.w,
        a.x + b.x,
        a.y + b.y,
        a.z + b.z
        );
}
