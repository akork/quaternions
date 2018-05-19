#ifndef SIMPLEOBJECT3D_H
#define SIMPLEOBJECT3D_H

#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QVector3D>
#include <QVector2D>
#include <QOpenGLFunctions>

class QOpenGLTexture;
class QOpenGLFunctions;
class QOpenGLShaderProgram;

struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
};

class SimpleObject3D : protected QOpenGLFunctions
{
public:
  SimpleObject3D();
  SimpleObject3D(const QVector<VertexData> &vertData, const QVector<GLushort> &indexes,
                 const QImage *texture = 0);
  ~SimpleObject3D();
  void init(const QVector<VertexData> &vertData, const QVector<GLushort> &indexes, const QImage *textureImage);
  void draw(QOpenGLShaderProgram *program);
  void initTexture(const QImage *textureImage);
private:
  QOpenGLBuffer arrayBuf;
  QOpenGLBuffer indexBuf;
  QMatrix4x4 modelMat;
  QOpenGLTexture *texture;
};

#endif // SIMPLEOBJECT3D_H
