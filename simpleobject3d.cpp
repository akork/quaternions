#include "simpleobject3d.h"
#include <QOpenGLTexture>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

SimpleObject3D::SimpleObject3D() :
  m_indexBuffer(QOpenGLBuffer::IndexBuffer), m_texture(0)
{

}

SimpleObject3D::SimpleObject3D(const QVector<VertexData> &vertData, const QVector<GLuint> &indexes, const QImage &texture) :
  m_indexBuffer(QOpenGLBuffer::IndexBuffer), m_texture(0)
{
  init(vertData, indexes, texture);
}

SimpleObject3D::~SimpleObject3D()
{
  if (m_vertexBuffer.isCreated())
    m_vertexBuffer.destroy();
  if (m_indexBuffer.isCreated())
    m_indexBuffer.destroy();
  if (m_texture != 0 && m_texture->isCreated())
    m_texture->destroy();
}

void SimpleObject3D::init(const QVector<VertexData> &vertData, const QVector<GLuint> &indexes, const QImage &texture)
{
  m_vertexBuffer.create();
  m_vertexBuffer.bind();
  m_vertexBuffer.allocate(vertData.constData(), vertData.size() * sizeof(VertexData));
  m_vertexBuffer.release();

  m_indexBuffer.create();
  m_indexBuffer.bind();
  m_indexBuffer.allocate(indexes.constData(), indexes.size() * sizeof(GLuint));
  m_indexBuffer.release();

  m_texture = new QOpenGLTexture(texture.mirrored());
}

void SimpleObject3D::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions)
{

}
