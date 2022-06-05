/****************************************************************************
** Meta object code from reading C++ file 'SpectrumFilterView.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/gui/spectrum/SpectrumFilterView.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SpectrumFilterView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GUI__spectrum__SpectrumFilterView_t {
    const uint offsetsAndSize[2];
    char stringdata0[34];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_GUI__spectrum__SpectrumFilterView_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_GUI__spectrum__SpectrumFilterView_t qt_meta_stringdata_GUI__spectrum__SpectrumFilterView = {
    {
QT_MOC_LITERAL(0, 33) // "GUI::spectrum::SpectrumFilter..."

    },
    "GUI::spectrum::SpectrumFilterView"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GUI__spectrum__SpectrumFilterView[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void GUI::spectrum::SpectrumFilterView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject GUI::spectrum::SpectrumFilterView::staticMetaObject = { {
    QMetaObject::SuperData::link<ImageView::staticMetaObject>(),
    qt_meta_stringdata_GUI__spectrum__SpectrumFilterView.offsetsAndSize,
    qt_meta_data_GUI__spectrum__SpectrumFilterView,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_GUI__spectrum__SpectrumFilterView_t
, QtPrivate::TypeAndForceComplete<SpectrumFilterView, std::true_type>



>,
    nullptr
} };


const QMetaObject *GUI::spectrum::SpectrumFilterView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GUI::spectrum::SpectrumFilterView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GUI__spectrum__SpectrumFilterView.stringdata0))
        return static_cast<void*>(this);
    return ImageView::qt_metacast(_clname);
}

int GUI::spectrum::SpectrumFilterView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ImageView::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
