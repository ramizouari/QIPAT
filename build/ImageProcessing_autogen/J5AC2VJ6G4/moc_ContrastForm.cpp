/****************************************************************************
** Meta object code from reading C++ file 'ContrastForm.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/gui/options/ContrastForm.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ContrastForm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GUI__options__ContrastForm_t {
    const uint offsetsAndSize[10];
    char stringdata0[76];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_GUI__options__ContrastForm_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_GUI__options__ContrastForm_t qt_meta_stringdata_GUI__options__ContrastForm = {
    {
QT_MOC_LITERAL(0, 26), // "GUI::options::ContrastForm"
QT_MOC_LITERAL(27, 12), // "valueUpdated"
QT_MOC_LITERAL(40, 0), // ""
QT_MOC_LITERAL(41, 15), // "requestPointAdd"
QT_MOC_LITERAL(57, 18) // "requestPointRemove"

    },
    "GUI::options::ContrastForm\0valueUpdated\0"
    "\0requestPointAdd\0requestPointRemove"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GUI__options__ContrastForm[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    3,   38,    2, 0x06,    1 /* Public */,
       3,    1,   45,    2, 0x06,    5 /* Public */,
       3,    0,   48,    2, 0x06,    7 /* Public */,
       4,    1,   49,    2, 0x06,    8 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void GUI::options::ContrastForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ContrastForm *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->valueUpdated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 1: _t->requestPointAdd((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->requestPointAdd(); break;
        case 3: _t->requestPointRemove((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ContrastForm::*)(int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContrastForm::valueUpdated)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ContrastForm::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContrastForm::requestPointAdd)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ContrastForm::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContrastForm::requestPointAdd)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ContrastForm::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContrastForm::requestPointRemove)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject GUI::options::ContrastForm::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_GUI__options__ContrastForm.offsetsAndSize,
    qt_meta_data_GUI__options__ContrastForm,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_GUI__options__ContrastForm_t
, QtPrivate::TypeAndForceComplete<ContrastForm, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>



>,
    nullptr
} };


const QMetaObject *GUI::options::ContrastForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GUI::options::ContrastForm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GUI__options__ContrastForm.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int GUI::options::ContrastForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void GUI::options::ContrastForm::valueUpdated(int _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GUI::options::ContrastForm::requestPointAdd(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GUI::options::ContrastForm::requestPointAdd()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void GUI::options::ContrastForm::requestPointRemove(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
struct qt_meta_stringdata_GUI__options__ContrastFormRow_t {
    const uint offsetsAndSize[8];
    char stringdata0[58];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_GUI__options__ContrastFormRow_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_GUI__options__ContrastFormRow_t qt_meta_stringdata_GUI__options__ContrastFormRow = {
    {
QT_MOC_LITERAL(0, 29), // "GUI::options::ContrastFormRow"
QT_MOC_LITERAL(30, 12), // "valueUpdated"
QT_MOC_LITERAL(43, 0), // ""
QT_MOC_LITERAL(44, 13) // "requestRemove"

    },
    "GUI::options::ContrastFormRow\0"
    "valueUpdated\0\0requestRemove"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GUI__options__ContrastFormRow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   26,    2, 0x06,    1 /* Public */,
       3,    0,   31,    2, 0x06,    4 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void,

       0        // eod
};

void GUI::options::ContrastFormRow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ContrastFormRow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->valueUpdated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 1: _t->requestRemove(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ContrastFormRow::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContrastFormRow::valueUpdated)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ContrastFormRow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContrastFormRow::requestRemove)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject GUI::options::ContrastFormRow::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_GUI__options__ContrastFormRow.offsetsAndSize,
    qt_meta_data_GUI__options__ContrastFormRow,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_GUI__options__ContrastFormRow_t
, QtPrivate::TypeAndForceComplete<ContrastFormRow, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>



>,
    nullptr
} };


const QMetaObject *GUI::options::ContrastFormRow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GUI::options::ContrastFormRow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GUI__options__ContrastFormRow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int GUI::options::ContrastFormRow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void GUI::options::ContrastFormRow::valueUpdated(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GUI::options::ContrastFormRow::requestRemove()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
struct qt_meta_stringdata_GUI__options__SplineContrastForm_t {
    const uint offsetsAndSize[12];
    char stringdata0[94];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_GUI__options__SplineContrastForm_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_GUI__options__SplineContrastForm_t qt_meta_stringdata_GUI__options__SplineContrastForm = {
    {
QT_MOC_LITERAL(0, 32), // "GUI::options::SplineContrastForm"
QT_MOC_LITERAL(33, 12), // "valueUpdated"
QT_MOC_LITERAL(46, 0), // ""
QT_MOC_LITERAL(47, 11), // "image::Real"
QT_MOC_LITERAL(59, 15), // "requestPointAdd"
QT_MOC_LITERAL(75, 18) // "requestPointRemove"

    },
    "GUI::options::SplineContrastForm\0"
    "valueUpdated\0\0image::Real\0requestPointAdd\0"
    "requestPointRemove"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GUI__options__SplineContrastForm[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    4,   38,    2, 0x06,    1 /* Public */,
       4,    1,   47,    2, 0x06,    6 /* Public */,
       4,    0,   50,    2, 0x06,    8 /* Public */,
       5,    1,   51,    2, 0x06,    9 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, 0x80000000 | 3,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void GUI::options::SplineContrastForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SplineContrastForm *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->valueUpdated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<image::Real>>(_a[4]))); break;
        case 1: _t->requestPointAdd((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->requestPointAdd(); break;
        case 3: _t->requestPointRemove((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SplineContrastForm::*)(int , int , int , image::Real );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SplineContrastForm::valueUpdated)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SplineContrastForm::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SplineContrastForm::requestPointAdd)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SplineContrastForm::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SplineContrastForm::requestPointAdd)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SplineContrastForm::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SplineContrastForm::requestPointRemove)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject GUI::options::SplineContrastForm::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_GUI__options__SplineContrastForm.offsetsAndSize,
    qt_meta_data_GUI__options__SplineContrastForm,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_GUI__options__SplineContrastForm_t
, QtPrivate::TypeAndForceComplete<SplineContrastForm, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<image::Real, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>



>,
    nullptr
} };


const QMetaObject *GUI::options::SplineContrastForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GUI::options::SplineContrastForm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GUI__options__SplineContrastForm.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int GUI::options::SplineContrastForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void GUI::options::SplineContrastForm::valueUpdated(int _t1, int _t2, int _t3, image::Real _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GUI::options::SplineContrastForm::requestPointAdd(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GUI::options::SplineContrastForm::requestPointAdd()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void GUI::options::SplineContrastForm::requestPointRemove(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
struct qt_meta_stringdata_GUI__options__SplineContrastFormRow_t {
    const uint offsetsAndSize[10];
    char stringdata0[76];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_GUI__options__SplineContrastFormRow_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_GUI__options__SplineContrastFormRow_t qt_meta_stringdata_GUI__options__SplineContrastFormRow = {
    {
QT_MOC_LITERAL(0, 35), // "GUI::options::SplineContrastF..."
QT_MOC_LITERAL(36, 12), // "valueUpdated"
QT_MOC_LITERAL(49, 0), // ""
QT_MOC_LITERAL(50, 11), // "image::Real"
QT_MOC_LITERAL(62, 13) // "requestRemove"

    },
    "GUI::options::SplineContrastFormRow\0"
    "valueUpdated\0\0image::Real\0requestRemove"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GUI__options__SplineContrastFormRow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    3,   26,    2, 0x06,    1 /* Public */,
       4,    0,   33,    2, 0x06,    5 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 3,    2,    2,    2,
    QMetaType::Void,

       0        // eod
};

void GUI::options::SplineContrastFormRow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SplineContrastFormRow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->valueUpdated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<image::Real>>(_a[3]))); break;
        case 1: _t->requestRemove(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SplineContrastFormRow::*)(int , int , image::Real );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SplineContrastFormRow::valueUpdated)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SplineContrastFormRow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SplineContrastFormRow::requestRemove)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject GUI::options::SplineContrastFormRow::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_GUI__options__SplineContrastFormRow.offsetsAndSize,
    qt_meta_data_GUI__options__SplineContrastFormRow,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_GUI__options__SplineContrastFormRow_t
, QtPrivate::TypeAndForceComplete<SplineContrastFormRow, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<image::Real, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>



>,
    nullptr
} };


const QMetaObject *GUI::options::SplineContrastFormRow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GUI::options::SplineContrastFormRow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GUI__options__SplineContrastFormRow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int GUI::options::SplineContrastFormRow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void GUI::options::SplineContrastFormRow::valueUpdated(int _t1, int _t2, image::Real _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GUI::options::SplineContrastFormRow::requestRemove()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
