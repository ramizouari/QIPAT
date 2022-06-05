/****************************************************************************
** Meta object code from reading C++ file 'SpectrumFilterDialog.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/gui/options/SpectrumFilterDialog.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SpectrumFilterDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GUI__options__SpectrumFilterDialog_t {
    const uint offsetsAndSize[10];
    char stringdata0[87];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_GUI__options__SpectrumFilterDialog_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_GUI__options__SpectrumFilterDialog_t qt_meta_stringdata_GUI__options__SpectrumFilterDialog = {
    {
QT_MOC_LITERAL(0, 34), // "GUI::options::SpectrumFilterD..."
QT_MOC_LITERAL(35, 7), // "preview"
QT_MOC_LITERAL(43, 0), // ""
QT_MOC_LITERAL(44, 5), // "apply"
QT_MOC_LITERAL(50, 36) // "std::pair<image::Image,image:..."

    },
    "GUI::options::SpectrumFilterDialog\0"
    "preview\0\0apply\0std::pair<image::Image,image::Image>"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GUI__options__SpectrumFilterDialog[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   26,    2, 0x0a,    1 /* Public */,
       3,    0,   27,    2, 0x10a,    2 /* Public | MethodIsConst  */,

 // slots: parameters
    QMetaType::Void,
    0x80000000 | 4,

       0        // eod
};

void GUI::options::SpectrumFilterDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SpectrumFilterDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->preview(); break;
        case 1: { std::pair<image::Image,image::Image> _r = _t->apply();
            if (_a[0]) *reinterpret_cast< std::pair<image::Image,image::Image>*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

const QMetaObject GUI::options::SpectrumFilterDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_GUI__options__SpectrumFilterDialog.offsetsAndSize,
    qt_meta_data_GUI__options__SpectrumFilterDialog,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_GUI__options__SpectrumFilterDialog_t
, QtPrivate::TypeAndForceComplete<SpectrumFilterDialog, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::pair<image::Image,image::Image>, std::false_type>


>,
    nullptr
} };


const QMetaObject *GUI::options::SpectrumFilterDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GUI::options::SpectrumFilterDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GUI__options__SpectrumFilterDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int GUI::options::SpectrumFilterDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
