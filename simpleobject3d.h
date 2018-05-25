#ifndef SIMPLEOBJECT3D_H
#define SIMPLEOBJECT3D_H

#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QVector3D>
#include <QVector2D>
#include <QOpenGLFunctions>
#include <QObject>
#include <QOpenGLTexture>

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

class QOpenGLTexture;
class QOpenGLFunctions;
class QOpenGLShaderProgram;

struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
};

class SimpleObject3D : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT
signals:
  void modelChanged(QQuaternion &quaternion);

public:
  int numIndices;
  GLenum mode;
  SimpleObject3D(const QVector<VertexData> &vertData, const QVector<GLushort> &indexes,
                 const QImage *texture = 0, GLenum mode = GL_TRIANGLE_STRIP);

  ~SimpleObject3D();
  void init(const QVector<VertexData> &vertices, const QVector<GLushort> &indices, const QImage *textureImage);
  void draw(QOpenGLShaderProgram *program);
  void initTexture(const QImage *textureImage);
  void setRotation(QQuaternion quaternion);
  void rotate(QQuaternion &quaternion);
  void scale(double factor);
  QQuaternion quaternion;
private:
  QOpenGLBuffer arrayBuf;
  QOpenGLBuffer indexBuf;
  QMatrix4x4 modelMat;
  QMatrix4x4 translation;
  QMatrix4x4 scaling;
  QOpenGLTexture *texture;
};


#endif // SIMPLEOBJECT3D_H
