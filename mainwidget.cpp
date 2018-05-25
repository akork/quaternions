/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwidget.h"

#include <QMouseEvent>
#include <QVector>

#include <math.h>

MainWidget::MainWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    cubeGeometry(0),
    texture(0),
    angularSpeed(0),
    window(parent)
{

}

MainWidget::~MainWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete texture;
    delete cubeGeometry;
    doneCurrent();
}

//! [0]
void MainWidget::mousePressEvent(QMouseEvent *e)
{
  if ((e->buttons() == Qt::LeftButton) || (e->buttons() == Qt::RightButton))
    mousePressPosition = QVector2D(e->localPos());
  e->accept();
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{
  quaternion = QQuaternion::fromEulerAngles(0, 0, 0);
  return;
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;
}

void MainWidget::mouseMoveEvent(QMouseEvent *e)
{
  if (e->buttons() == Qt::LeftButton)
  {
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;
    double angle = diff.length()/3;
    int direction = -1;
    vert_angle = vert_angle + direction * (e->localPos().y() - mousePressPosition.y()) / 100;
    hor_angle -= (e->localPos().x() - mousePressPosition.x()) / 100;
    double pitch = (e->localPos().y() - mousePressPosition.y()) / 2;
    double yaw = (e->localPos().x() - mousePressPosition.x()) / 2;
    mousePressPosition = QVector2D(e->localPos());
    QVector3D axis = QVector3D(diff.y(), diff.x(), 0);

//    axis = cameraQuat;
    auto axisQuat = QQuaternion(0.0f, axis);
    auto cameraInv = cameraQuat.inverted();
    auto modelQuat = objects[0]->quaternion;
    auto modelInv = modelQuat.inverted();
    axisQuat = modelInv * cameraInv * axisQuat * cameraInv.conjugated() * modelInv.conjugated();
//    quaternion = QQuaternion::fromEulerAngles(pitch, yaw, 0);
    quaternion = QQuaternion::fromAxisAndAngle(axisQuat.vector(), angle);



//    quaternion = cameraQuat * quaternion;
//    quaternion = cameraQuat * quaternion * cameraQuat.conjugated();

//    auto modelQuat = objects[0]->quaternion;
//    modelQuat *= cameraQuat.inverted();
//    modelQuat *= quaternion;
//    modelQuat *= cameraQuat;

    objects[0]->rotate(quaternion);
    objects[1]->rotate(quaternion);
//    auto modelMat = objects[0]->modelMat;
//    modelMat *= viewMatrix;
//    modelMat.rotate(quaternion);
//    modelMat *= viewMatrix.inverted();
    needToUpdate = true;
 }
  if (e->buttons() == Qt::RightButton)
  {
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;
    double angle = diff.length()/3;
    int direction = -1;
    vert_angle = vert_angle + direction * (e->localPos().y() - mousePressPosition.y()) / 100;
    hor_angle -= (e->localPos().x() - mousePressPosition.x()) / 100;
    double pitch = (e->localPos().y() - mousePressPosition.y()) / 2;
    double yaw = (e->localPos().x() - mousePressPosition.x()) / 2;
    mousePressPosition = QVector2D(e->localPos());
    QVector3D axis = QVector3D(diff.y(), diff.x(), 0);


    quaternion = QQuaternion::fromEulerAngles(pitch, yaw, 0);
    quaternion = QQuaternion::fromAxisAndAngle(axis, angle);
    cameraQuat = quaternion * cameraQuat;
    QMatrix4x4 rotateMat;
    rotateMat.setToIdentity();
    rotateMat.rotate(cameraQuat);
    QMatrix4x4 translateMat;
    translateMat.setToIdentity();
    translateMat.translate(0, 0, -6);
    viewMatrix = translateMat * rotateMat;
    needToUpdate = true;
  }
}
//! [0]

void MainWidget::initializeGL()
{
    initializeOpenGLFunctions();

//    glClearColor(0, 0, 0, 1);
    glClearColor(1, 1, 1, 1);

    initShaders();

//! [2]
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
//    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//! [2]


    cubeGeometry = new CubeGeometry;
    initObjects();
    connect(this, SIGNAL(modelChanged(QQuaternion, Quaternion)),
            window, SLOT(updateVariables(QQuaternion, Quaternion)));

    cameraQuat = QQuaternion(1, 0, 0, 0);
    QMatrix4x4 rotateMat;
    rotateMat.setToIdentity();
    rotateMat.rotate(cameraQuat);
    QMatrix4x4 translateMat;
    translateMat.setToIdentity();
    translateMat.translate(0, 0, -6);

    viewMatrix = translateMat * rotateMat;
    timer.start(20, this);
//    viewMatrix.setToIdentity();
//    viewMatrix.lookAt(QVector3D(0, 0, -5), QVector3D(0, 0, 0), QVector3D(0, 1, 0));
}

//! [3]
void MainWidget::initShaders()
{
//     Compile vertex  shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();

//    static const char *vertexShaderSource =
//        "attribute highp vec4 a_position;\n"
//        "void main() {\n"
//        "   gl_Position = a_position;\n"
//        "}\n";

//    static const char *fragmentShaderSource =
//        "void main() {\n"
//        "   gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
//        "}\n";

//        program2.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
//        program2.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
//        program2.link();
//    program2.bind();

}

void MainWidget::initObjects()
{
//  objects.append(new SimpleObject3D(cubeGeometry->vertices, cubeGeometry->indices, new QImage(":/cube.png")));
  LineGeometry lineGeometry;
  objects.append(new SimpleObject3D(cubeGeometry->vertices, cubeGeometry->indices, new QImage(":/minecraft.jpg"), GL_TRIANGLE_STRIP));
//  objects.append(new SimpleObject3D(cubeGeometry->vertices, cubeGeometry->indices, new QImage(":/minecraft.jpg")));
  objects.append(new SimpleObject3D(lineGeometry.vertices, lineGeometry.indices, new QImage(":/palette.png"), GL_LINES));
  objects.append(new SimpleObject3D(lineGeometry.vertices, lineGeometry.indices, new QImage(":/palette.png"), GL_LINES));
  objects[1]->scale(0.5);

  objects[2]->scale(2);
}

void MainWidget::timerEvent(QTimerEvent *e)
{
  if (needToUpdate)
  {
    update();
    auto q = objects[0]->quaternion;
    emit modelChanged(objects[0]->quaternion, Quaternion(q.scalar(), q.x(), q.y(), q.z()));
    needToUpdate = false;
  }
}

void MainWidget::updateScene(KinematicVariables vars)
{
  rotation = QQuaternion(vars.scalar, vars.xpos, vars.ypos, vars.zpos).normalized();
  objects[0]->setRotation(rotation);
  objects[1]->setRotation(rotation);
  needToUpdate = true;
//  viewMatrix.setToIdentity();
//  double scale = 5;
//  viewMatrix.lookAt(QVector3D(scale*sin(vars.t), 5, -scale*cos(vars.t)), QVector3D(0, 0, 0), QVector3D(0, 1, 0));
//  update();
}

void MainWidget::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 3.0, zFar = 70.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}
//! [5]

void MainWidget::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // Calculate model view transformation
    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -6.0);
//    matrix.rotate(rotation);

//    matrix.setToIdentity();
    // Set modelview-projection matrix

    program.setUniformValue("u_projectionMatrix", projection);
    program.setUniformValue("u_viewMatrix", viewMatrix);
//! [6]

    // Use texture unit 0 which contains cube.png

    // Draw cube geometry
    for (int i = 2; i >= 0; --i)
      objects[i]->draw(&program);
}
