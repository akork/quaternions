#ifndef SIMPLELINE_H
#define SIMPLELINE_H

#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QVector3D>
#include <QVector2D>
#include <QOpenGLFunctions>
#include "simpleobject3d.h"

class QOpenGLTexture;
class QOpenGLFunctions;
class QOpenGLShaderProgram;

class SimpleLine : protected QOpenGLFunctions
{
public:
  SimpleLine(const QVector<VertexData> &vertData, const QVector<GLushort> &indexes,
                 const QImage *texture = 0);
  ~SimpleLine();
  void init(const QVector<VertexData> &vertData, const QVector<GLushort> &indexes, const QImage *textureImage);
  void draw(QOpenGLShaderProgram *program);
  void initTexture(const QImage *textureImage);
  void setRotation(QQuaternion quaternion);
  void rotate(QQuaternion quaternion);
private:
  QOpenGLBuffer arrayBuf;
  QOpenGLBuffer indexBuf;
  QMatrix4x4 modelMat;
  QOpenGLTexture *texture;
};

#endif // SIMPLELINE_H
