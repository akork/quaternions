#include "simpleobject3d.h"

SimpleObject3D::SimpleObject3D(const QVector<VertexData> &vertData, const QVector<GLushort> &indexes, const QImage *texture, GLenum mode) :
  indexBuf(QOpenGLBuffer::IndexBuffer), texture(0), mode(mode)
{
  initializeOpenGLFunctions();
  arrayBuf.create();
  indexBuf.create();
  modelMat.setToIdentity();
  init(vertData, indexes, texture);
}

SimpleObject3D::~SimpleObject3D()
{
  if (arrayBuf.isCreated())
    arrayBuf.destroy();
  if (indexBuf.isCreated())
    indexBuf.destroy();
  if (texture != 0 && texture->isCreated())
    texture->destroy();
}

void SimpleObject3D::init(const QVector<VertexData> &vertices, const QVector<GLushort> &indices, const QImage *textureImage)
{
  initTexture(textureImage);

  numIndices = indices.length();
  // Transfer vertex data to VBO 0
  arrayBuf.bind();
  arrayBuf.allocate(vertices.constData(), vertices.length() * sizeof(VertexData));
  arrayBuf.release();

  // Transfer index data to VBO 1
  indexBuf.bind();
  indexBuf.allocate(indices.constData(), indices.length() * sizeof(GLushort));
  indexBuf.release();

  quaternion = QQuaternion(1, 0, 0, 0);
  translation.setToIdentity();
  scaling.setToIdentity();
}

void SimpleObject3D::draw(QOpenGLShaderProgram *program)
{
  // Tell OpenGL which VBOs to use
  arrayBuf.bind();
  indexBuf.bind();

  // Offset for position
  quintptr offset = 0;

  // Tell OpenGL programmable pipeline how to locate vertex position data
  int vertexLocation = program->attributeLocation("a_position");
  program->enableAttributeArray(vertexLocation);
  program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

  // Offset for texture coordinate
  offset += sizeof(QVector3D);

  // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
  int texcoordLocation = program->attributeLocation("a_texcoord");
  program->enableAttributeArray(texcoordLocation);
  program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

  texture->bind();
  program->setUniformValue("texture", 0);

  modelMat.setToIdentity();
  modelMat.rotate(quaternion);
  modelMat *= scaling * translation;

  program->setUniformValue("u_modelMatrix", modelMat);
  // Draw cube geometry using indices from VBO 1
  glLineWidth((GLfloat)10);
  glDrawElements(mode, numIndices, GL_UNSIGNED_SHORT, 0);
}

void SimpleObject3D::setRotation(QQuaternion quaternion)
{
  this->quaternion = quaternion;
//  emit modelChanged(this->quaternion);
}

void SimpleObject3D::rotate(QQuaternion &quaternion)
{
  this->quaternion *= quaternion;
//  emit modelChanged(this->quaternion);
}

void SimpleObject3D::scale(double factor)
{
  scaling.scale(factor);
}

void SimpleObject3D::initTexture(const QImage *textureImage)
{
  if (!textureImage) return;
  // Load cube.png image
  texture = new QOpenGLTexture(textureImage->mirrored());
  //    texture = new QOpenGLTexture(QImage(":/cube.png").mirrored());

  // Set nearest filtering mode for texture minification
  texture->setMinificationFilter(QOpenGLTexture::Nearest);

  // Set bilinear filtering mode for texture magnification
  texture->setMagnificationFilter(QOpenGLTexture::Linear);

  // Wrap texture coordinates by repeating
  // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
  texture->setWrapMode(QOpenGLTexture::Repeat);
}
