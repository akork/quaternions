#include "simpleline.h"

#include <QOpenGLTexture>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

SimpleLine::SimpleLine(const QVector<VertexData> &vertData, const QVector<GLushort> &indexes, const QImage *texture) :
  indexBuf(QOpenGLBuffer::IndexBuffer), texture(0)
{
  initializeOpenGLFunctions();
  arrayBuf.create();
  indexBuf.create();
  modelMat.setToIdentity();
  init(vertData, indexes, texture);
}

SimpleLine::~SimpleLine()
{
  if (arrayBuf.isCreated())
    arrayBuf.destroy();
  if (indexBuf.isCreated())
    indexBuf.destroy();
  if (texture != 0 && texture->isCreated())
    texture->destroy();
}

void SimpleLine::initTexture(const QImage *textureImage)
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

void SimpleLine::setRotation(QQuaternion quaternion)
{
  modelMat.setToIdentity();
  modelMat.rotate(quaternion);
}

void SimpleLine::rotate(QQuaternion quaternion)
{
  modelMat.rotate(quaternion);
}

void SimpleLine::init(const QVector<VertexData> &vertices, const QVector<GLushort> &indices, const QImage *textureImage)
{
//  initTexture(textureImage);

    QVector<QVector3D> vvertices =
    {
        QVector3D(0.0f, 0.0f,  0.0f),
        QVector3D( 0.0f, 0.0f,  10.0f)
    };
  // Transfer vertex data to VBO 0
  arrayBuf.bind();
  arrayBuf.allocate(vvertices.constData(), 2 * sizeof(QVector3D));
  arrayBuf.release();

//  // Transfer index data to VBO 1
//  indexBuf.bind();
//  indexBuf.allocate(indices.constData(), 34 * sizeof(GLushort));
//  indexBuf.release();
}

void SimpleLine::draw(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
//    indexBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(QVector3D));
    program->release();

//    // Offset for texture coordinate
//    offset += sizeof(QVector3D);

//    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
//    int texcoordLocation = program->attributeLocation("a_texcoord");
//    program->enableAttributeArray(texcoordLocation);
//    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

//    texture->bind();
//    program->setUniformValue("texture", 0);
//    program->setUniformValue("u_modelMatrix", modelMat);
    // Draw cube geometry using indices from VBO 1

    glDrawArrays(GL_LINES, 0, 10);
}
