/****************************************************************************
** Meta object code from reading C++ file 'init.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Source/init.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'init.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Init_t {
    QByteArrayData data[7];
    char stringdata[68];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Init_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Init_t qt_meta_stringdata_Init = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Init"
QT_MOC_LITERAL(1, 5, 13), // "settingsSaved"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 8), // "Settings"
QT_MOC_LITERAL(4, 29, 8), // "settings"
QT_MOC_LITERAL(5, 38, 14), // "hotkey1clicked"
QT_MOC_LITERAL(6, 53, 14) // "hotkey2clicked"

    },
    "Init\0settingsSaved\0\0Settings\0settings\0"
    "hotkey1clicked\0hotkey2clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Init[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x08 /* Private */,
       5,    0,   32,    2, 0x08 /* Private */,
       6,    0,   33,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Init::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Init *_t = static_cast<Init *>(_o);
        switch (_id) {
        case 0: _t->settingsSaved((*reinterpret_cast< Settings(*)>(_a[1]))); break;
        case 1: _t->hotkey1clicked(); break;
        case 2: _t->hotkey2clicked(); break;
        default: ;
        }
    }
}

const QMetaObject Init::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Init.data,
      qt_meta_data_Init,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Init::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Init::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Init.stringdata))
        return static_cast<void*>(const_cast< Init*>(this));
    return QWidget::qt_metacast(_clname);
}

int Init::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
