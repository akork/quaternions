#include "simpleobject3d.h"
#include <QOpenGLTexture>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

SimpleObject3D::SimpleObject3D() :
  indexBuf(QOpenGLBuffer::IndexBuffer), texture(0)
{

}

SimpleObject3D::SimpleObject3D(const QVector<VertexData> &vertData, const QVector<GLushort> &indexes, const QImage *texture) :
  indexBuf(QOpenGLBuffer::IndexBuffer), texture(0)
{
  initializeOpenGLFunctions();
  arrayBuf.create();
  indexBuf.create();
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

void SimpleObject3D::init(const QVector<VertexData> &vertices, const QVector<GLushort> &indices, const QImage *textureImage)
{
  initTexture(textureImage);

  // Transfer vertex data to VBO 0
  arrayBuf.bind();
  arrayBuf.allocate(vertices.constData(), 24 * sizeof(VertexData));
  arrayBuf.release();

  // Transfer index data to VBO 1
  indexBuf.bind();
  indexBuf.allocate(indices.constData(), 34 * sizeof(GLushort));
  indexBuf.release();
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
    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_SHORT, 0);
}
