#ifndef SIMPLEOBJECT3D_H
#define SIMPLEOBJECT3D_H

#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QVector3D>
#include <QVector2D>

class QOpenGLTexture;
class QOpenGLFunctions;
class QOpenGLShaderProgram;

struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
};

class SimpleObject3D
{
public:
  SimpleObject3D();
  SimpleObject3D(const QVector<VertexData> &vertData, const QVector<GLuint> &indexes,
                 const QImage &texture);
  ~SimpleObject3D();
  void init(const QVector<VertexData> &vertData, const QVector<GLuint> &indexes, const QImage &texture);
  void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions);

private:
  QOpenGLBuffer m_vertexBuffer;
  QOpenGLBuffer m_indexBuffer;
  QMatrix4x4 m_modelMatrix;
  QOpenGLTexture *m_texture;
};

#endif // SIMPLEOBJECT3D_H
