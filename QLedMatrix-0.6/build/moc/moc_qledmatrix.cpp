/****************************************************************************
** Meta object code from reading C++ file 'qledmatrix.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qledmatrix.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qledmatrix.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QLedMatrix[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       5,   14, // properties
       1,   29, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
      18,   11, 0x43095103,
      45,   34, 0x0009510b,
      60,   11, 0x43095103,
      77,   73, 0x02095003,
      82,   73, 0x02095003,

 // enums: name, flags, count, data
      90, 0x0,    8,   33,

 // enum data: key, value
      99, uint(QLedMatrix::NoColor),
     107, uint(QLedMatrix::Red),
     111, uint(QLedMatrix::Green),
     117, uint(QLedMatrix::Blue),
     122, uint(QLedMatrix::White),
     128, uint(QLedMatrix::Orange),
     135, uint(QLedMatrix::OrangeRed),
     145, uint(QLedMatrix::Yellow),

       0        // eod
};

static const char qt_meta_stringdata_QLedMatrix[] = {
    "QLedMatrix\0QColor\0backgroundColor\0"
    "Qt::BGMode\0backgroundMode\0darkLedColor\0"
    "int\0rows\0columns\0LEDColor\0NoColor\0Red\0"
    "Green\0Blue\0White\0Orange\0OrangeRed\0"
    "Yellow\0"
};

const QMetaObject QLedMatrix::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QLedMatrix,
      qt_meta_data_QLedMatrix, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QLedMatrix::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QLedMatrix::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QLedMatrix::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QLedMatrix))
        return static_cast<void*>(const_cast< QLedMatrix*>(this));
    return QWidget::qt_metacast(_clname);
}

int QLedMatrix::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
     if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QColor*>(_v) = backgroundColor(); break;
        case 1: *reinterpret_cast< Qt::BGMode*>(_v) = backgroundMode(); break;
        case 2: *reinterpret_cast< QColor*>(_v) = darkLedColor(); break;
        case 3: *reinterpret_cast< int*>(_v) = rowCount(); break;
        case 4: *reinterpret_cast< int*>(_v) = columnCount(); break;
        }
        _id -= 5;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setBackgroundColor(*reinterpret_cast< QColor*>(_v)); break;
        case 1: setBackgroundMode(*reinterpret_cast< Qt::BGMode*>(_v)); break;
        case 2: setDarkLedColor(*reinterpret_cast< QColor*>(_v)); break;
        case 3: setRowCount(*reinterpret_cast< int*>(_v)); break;
        case 4: setColumnCount(*reinterpret_cast< int*>(_v)); break;
        }
        _id -= 5;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
