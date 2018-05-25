/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
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

#include "borderlayout.h"
#include "window.h"
#include "mainwidget.h"
#include <QTextBrowser>
#include <QLabel>
#include <QHeaderView>
#include <QSizePolicy>
#include <QLineEdit>
#include <QPushButton>

QLabel * Window::fixedLabel(QString str)
{
  auto lbl = new QLabel(str);
  lbl->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  return lbl;
}

QTableWidget * Window::createTable(int nrows, int ncols)
{
    auto tableWidget = new QTableWidget();
    tableWidget->setRowCount(nrows);
    tableWidget->setColumnCount(ncols);
    tableWidget->setColumnWidth(0, 60);
    tableWidget->setColumnWidth(1, 70);
    tableWidget->verticalHeader()->hide();
    tableWidget->horizontalHeader()->hide();
    tableWidget->setShowGrid(false);
//    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->horizontalHeader()->setStretchLastSection(true);
    tableWidget->setStyleSheet("QHeaderView {background-color: transparent;}");

    float nTableHeight =
      (nrows * tableWidget->rowHeight(0)) +
      tableWidget->horizontalHeader()->height() +
      2 * tableWidget->frameWidth() + 2;

    tableWidget->setMaximumHeight(nTableHeight);

    return tableWidget;
}

Window::Window()
{
    mainWidget = new MainWidget(this);

    setWindowTitle(tr("Quaternion"));

    timeLabel = fixedLabel("");
    quaternTable = createTable(4, 2);
    quaternTable->setItem(0, 0, new QTableWidgetItem("scalar"));
    quaternTable->setItem(1, 0, new QTableWidgetItem("x"));
    quaternTable->setItem(2, 0, new QTableWidgetItem("y"));
    quaternTable->setItem(3, 0, new QTableWidgetItem("z"));
    quaternTable->setItem(0, 1, new QTableWidgetItem("1"));
    quaternTable->setItem(1, 1, new QTableWidgetItem("0"));
    quaternTable->setItem(2, 1, new QTableWidgetItem("0"));
    quaternTable->setItem(3, 1, new QTableWidgetItem("0"));

    quaternTable2 = createTable(4, 2);
    quaternTable2->setItem(0, 0, new QTableWidgetItem("scalar"));
    quaternTable2->setItem(1, 0, new QTableWidgetItem("x"));
    quaternTable2->setItem(2, 0, new QTableWidgetItem("y"));
    quaternTable2->setItem(3, 0, new QTableWidgetItem("z"));
    quaternTable2->setItem(0, 1, new QTableWidgetItem("1"));
    quaternTable2->setItem(1, 1, new QTableWidgetItem("0"));
    quaternTable2->setItem(2, 1, new QTableWidgetItem("0"));
    quaternTable2->setItem(3, 1, new QTableWidgetItem("0"));

    eulerTable = createTable(3, 2);
    eulerTable->setItem(0, 0, new QTableWidgetItem("alpha"));
    eulerTable->setItem(1, 0, new QTableWidgetItem("beta"));
    eulerTable->setItem(2, 0, new QTableWidgetItem("gamma"));
    eulerTable->setItem(0, 1, new QTableWidgetItem("0"));
    eulerTable->setItem(1, 1, new QTableWidgetItem("0"));
    eulerTable->setItem(2, 1, new QTableWidgetItem("0"));

    eulerTable2 = createTable(3, 2);
    eulerTable2->setItem(0, 0, new QTableWidgetItem("alpha"));
    eulerTable2->setItem(1, 0, new QTableWidgetItem("beta"));
    eulerTable2->setItem(2, 0, new QTableWidgetItem("gamma"));

    omegaTable = createTable(5, 2);
    omegaTable->setItem(0, 0, new QTableWidgetItem("o1"));
    omegaTable->setItem(1, 0, new QTableWidgetItem("o2"));
    omegaTable->setItem(2, 0, new QTableWidgetItem("o3"));
    omegaTable->setItem(3, 0, new QTableWidgetItem("tend"));
    omegaTable->setItem(4, 0, new QTableWidgetItem("step"));
    omegaTable->setItem(0, 1, new QTableWidgetItem("0"));
    omegaTable->setItem(1, 1, new QTableWidgetItem("1"));
    omegaTable->setItem(2, 1, new QTableWidgetItem("0"));
    omegaTable->setItem(3, 1, new QTableWidgetItem("10"));
    omegaTable->setItem(4, 1, new QTableWidgetItem("0.1"));
    for (int i = 0; i < 3; ++i)
      omegaTable->item(i, 0)->setFlags(
            omegaTable->item(i, 0)->flags() ^ Qt::ItemIsEditable);

    buttonsWidget = new QWidget(this);
    button1 = new QPushButton("Сброс");
    button2 = new QPushButton("Анимация");
    button3 = new QPushButton("Расчет и анимация");
    auto layout = new QGridLayout;
    layout->setVerticalSpacing(1);
    layout->setHorizontalSpacing(1);

    layout->addWidget(button1, 0, 0);
    layout->addWidget(button2, 0, 1);
    layout->addWidget(button3, 1, 0, 1, 2);
    buttonsWidget->setLayout(layout);

    auto leftLayout = new QVBoxLayout;
    leftLayout->addWidget(timeLabel);
    leftLayout->addWidget(fixedLabel("Кватернион"));
    leftLayout->addWidget(quaternTable);
//    leftLayout->addWidget(fixedLabel("Кватернион2"));
//    leftLayout->addWidget(quaternTable2);
//    leftLayout->addWidget(fixedLabel("Углы эйлера"));
//    leftLayout->addWidget(eulerTable);
    leftLayout->addWidget(fixedLabel("Углы эйлера"));
    leftLayout->addWidget(eulerTable2);
    leftLayout->addWidget(fixedLabel("Угловая скорость"));
    leftLayout->addWidget(omegaTable);
    leftLayout->addWidget(buttonsWidget);
    leftLayout->addWidget(new QWidget);

    auto leftWidget = new QWidget(this);
    leftWidget->setLayout(leftLayout);
    leftWidget->setMaximumWidth(200);

    auto layout2 = new QGridLayout;
    layout2->addWidget(leftWidget, 0, 0);
    layout2->addWidget(mainWidget, 0, 1);
    setLayout(layout2);


    controller = new Controller(this, this);

    connect(controller, SIGNAL(state_changed(KinematicVariables)),
            mainWidget, SLOT(updateScene(KinematicVariables)));
    connect(controller, SIGNAL(state_changed(KinematicVariables)),
            this, SLOT(updateTime(KinematicVariables)));
//    connect(omegaTable, SIGNAL(cellChanged(int,int)),
//            controller, SLOT(integrate_and_start()));
    connect(button1, SIGNAL(clicked()),
            controller, SLOT(reset_ic()));
    connect(button2, SIGNAL(clicked()),
            controller, SLOT(animation()));
    connect(button3, SIGNAL(clicked()),
            controller, SLOT(integrate_and_start()));
}

QLabel *Window::createLabel(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setFrameStyle(QFrame::Box | QFrame::Raised);
    return label;
}

auto tableItemFromNumber(float num)
{
  return new QTableWidgetItem(QString::number(num));
}

void Window::updateVariables(QQuaternion quaternion, Quaternion q)
{
    quaternTable->setItem(0, 1, tableItemFromNumber(quaternion.scalar()));
    quaternTable->setItem(1, 1, tableItemFromNumber(quaternion.x()));
    quaternTable->setItem(2, 1, tableItemFromNumber(quaternion.y()));
    quaternTable->setItem(3, 1, tableItemFromNumber(quaternion.z()));

    QVector3D angles = quaternion.toEulerAngles();

    eulerTable->setItem(0, 1, tableItemFromNumber(angles.x()));
    eulerTable->setItem(1, 1, tableItemFromNumber(angles.y()));
    eulerTable->setItem(2, 1, tableItemFromNumber(angles.z()));

    quaternTable2->setItem(0, 1, tableItemFromNumber(q.getW()));
    quaternTable2->setItem(1, 1, tableItemFromNumber(q.getX()));
    quaternTable2->setItem(2, 1, tableItemFromNumber(q.getY()));
    quaternTable2->setItem(3, 1, tableItemFromNumber(q.getZ()));

    angles = q.toEulerAngles();

    eulerTable2->setItem(0, 1, tableItemFromNumber(angles.x()));
    eulerTable2->setItem(1, 1, tableItemFromNumber(angles.y()));
    eulerTable2->setItem(2, 1, tableItemFromNumber(angles.z()));
}

void Window::updateTime(KinematicVariables vars)
{
  timeLabel->setText("Время: " + QString::number(vars.t));
}
