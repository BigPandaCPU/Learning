/****************************************************************************
** Meta object code from reading C++ file 'viewimage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "viewimage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'viewimage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_viewImage_t {
    QByteArrayData data[10];
    char stringdata[163];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_viewImage_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_viewImage_t qt_meta_stringdata_viewImage = {
    {
QT_MOC_LITERAL(0, 0, 9), // "viewImage"
QT_MOC_LITERAL(1, 10, 16), // "lineEdit_changed"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 23), // "pushButton_path_clicked"
QT_MOC_LITERAL(4, 52, 23), // "pushButton_load_clicked"
QT_MOC_LITERAL(5, 76, 23), // "pushButton_each_clicked"
QT_MOC_LITERAL(6, 100, 22), // "pushButton_all_clicked"
QT_MOC_LITERAL(7, 123, 15), // "mywidget_closed"
QT_MOC_LITERAL(8, 139, 1), // "i"
QT_MOC_LITERAL(9, 141, 21) // "lineEdit_changed_slot"

    },
    "viewImage\0lineEdit_changed\0\0"
    "pushButton_path_clicked\0pushButton_load_clicked\0"
    "pushButton_each_clicked\0pushButton_all_clicked\0"
    "mywidget_closed\0i\0lineEdit_changed_slot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_viewImage[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   50,    2, 0x0a /* Public */,
       4,    0,   51,    2, 0x0a /* Public */,
       5,    0,   52,    2, 0x0a /* Public */,
       6,    0,   53,    2, 0x0a /* Public */,
       7,    1,   54,    2, 0x0a /* Public */,
       9,    0,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,

       0        // eod
};

void viewImage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        viewImage *_t = static_cast<viewImage *>(_o);
        switch (_id) {
        case 0: _t->lineEdit_changed(); break;
        case 1: _t->pushButton_path_clicked(); break;
        case 2: _t->pushButton_load_clicked(); break;
        case 3: _t->pushButton_each_clicked(); break;
        case 4: _t->pushButton_all_clicked(); break;
        case 5: _t->mywidget_closed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->lineEdit_changed_slot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (viewImage::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&viewImage::lineEdit_changed)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject viewImage::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_viewImage.data,
      qt_meta_data_viewImage,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *viewImage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *viewImage::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_viewImage.stringdata))
        return static_cast<void*>(const_cast< viewImage*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int viewImage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void viewImage::lineEdit_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
