/****************************************************************************
** Meta object code from reading C++ file 'simpleobject3d.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../simpleobject3d.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'simpleobject3d.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SimpleObject3D_t {
    QByteArrayData data[5];
    char stringdata0[53];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SimpleObject3D_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SimpleObject3D_t qt_meta_stringdata_SimpleObject3D = {
    {
QT_MOC_LITERAL(0, 0, 14), // "SimpleObject3D"
QT_MOC_LITERAL(1, 15, 12), // "modelChanged"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 12), // "QQuaternion&"
QT_MOC_LITERAL(4, 42, 10) // "quaternion"

    },
    "SimpleObject3D\0modelChanged\0\0QQuaternion&\0"
    "quaternion"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SimpleObject3D[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void SimpleObject3D::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SimpleObject3D *_t = static_cast<SimpleObject3D *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->modelChanged((*reinterpret_cast< QQuaternion(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SimpleObject3D::*_t)(QQuaternion & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SimpleObject3D::modelChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject SimpleObject3D::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SimpleObject3D.data,
      qt_meta_data_SimpleObject3D,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SimpleObject3D::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SimpleObject3D::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SimpleObject3D.stringdata0))
        return static_cast<void*>(const_cast< SimpleObject3D*>(this));
    if (!strcmp(_clname, "QOpenGLFunctions"))
        return static_cast< QOpenGLFunctions*>(const_cast< SimpleObject3D*>(this));
    return QObject::qt_metacast(_clname);
}

int SimpleObject3D::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void SimpleObject3D::modelChanged(QQuaternion & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
