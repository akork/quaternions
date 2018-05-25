QT       += core gui widgets

INCLUDEPATH +=  /usr/local/Cellar/boost/1.67.0_1/include/
INCLUDEPATH +=  /exprtk

CONFIG += c++14

TARGET = cube
TEMPLATE = app

SOURCES += main.cpp \
    window.cpp \
    borderlayout.cpp \
    controller.cpp \
    ode.cpp \
    kinematicvariables.cpp \
    simpleobject3d.cpp \
    simpleline.cpp \
    quaternion.cpp

SOURCES += \
    mainwidget.cpp \
    geometryengine.cpp

HEADERS += \
    mainwidget.h \
    geometryengine.h \
    window.h \
    borderlayout.h \
    controller.h \
    ode.h \
    kinematicvariables.h \
    simpleobject3d.h \
    simpleline.h \
    quaternion.h

RESOURCES += \
    shaders.qrc \
    textures.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/cube
INSTALLS += target
