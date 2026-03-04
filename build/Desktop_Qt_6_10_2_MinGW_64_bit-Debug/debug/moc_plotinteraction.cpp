/****************************************************************************
** Meta object code from reading C++ file 'plotinteraction.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../plotinteraction.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plotinteraction.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN15PlotInteractionE_t {};
} // unnamed namespace

template <> constexpr inline auto PlotInteraction::qt_create_metaobjectdata<qt_meta_tag_ZN15PlotInteractionE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PlotInteraction",
        "requested",
        "",
        "QPointF",
        "delta",
        "moving",
        "pos",
        "leaved",
        "leave",
        "wheel",
        "localPos",
        "clicked",
        "Qt::MouseButton",
        "button",
        "creating"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'requested'
        QtMocHelpers::SignalData<void(QPointF)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'moving'
        QtMocHelpers::SignalData<void(QPointF)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 6 },
        }}),
        // Signal 'leaved'
        QtMocHelpers::SignalData<void(bool)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 8 },
        }}),
        // Signal 'wheel'
        QtMocHelpers::SignalData<void(QPointF, int)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 10 }, { QMetaType::Int, 4 },
        }}),
        // Signal 'clicked'
        QtMocHelpers::SignalData<void(QPointF, Qt::MouseButton)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 6 }, { 0x80000000 | 12, 13 },
        }}),
        // Slot 'creating'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PlotInteraction, qt_meta_tag_ZN15PlotInteractionE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PlotInteraction::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15PlotInteractionE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15PlotInteractionE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN15PlotInteractionE_t>.metaTypes,
    nullptr
} };

void PlotInteraction::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PlotInteraction *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->requested((*reinterpret_cast<std::add_pointer_t<QPointF>>(_a[1]))); break;
        case 1: _t->moving((*reinterpret_cast<std::add_pointer_t<QPointF>>(_a[1]))); break;
        case 2: _t->leaved((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 3: _t->wheel((*reinterpret_cast<std::add_pointer_t<QPointF>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2]))); break;
        case 4: _t->clicked((*reinterpret_cast<std::add_pointer_t<QPointF>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<Qt::MouseButton>>(_a[2]))); break;
        case 5: _t->creating(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (PlotInteraction::*)(QPointF )>(_a, &PlotInteraction::requested, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (PlotInteraction::*)(QPointF )>(_a, &PlotInteraction::moving, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (PlotInteraction::*)(bool )>(_a, &PlotInteraction::leaved, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (PlotInteraction::*)(QPointF , int )>(_a, &PlotInteraction::wheel, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (PlotInteraction::*)(QPointF , Qt::MouseButton )>(_a, &PlotInteraction::clicked, 4))
            return;
    }
}

const QMetaObject *PlotInteraction::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlotInteraction::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15PlotInteractionE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QGraphicsRectItem"))
        return static_cast< QGraphicsRectItem*>(this);
    return QObject::qt_metacast(_clname);
}

int PlotInteraction::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void PlotInteraction::requested(QPointF _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void PlotInteraction::moving(QPointF _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void PlotInteraction::leaved(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void PlotInteraction::wheel(QPointF _t1, int _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1, _t2);
}

// SIGNAL 4
void PlotInteraction::clicked(QPointF _t1, Qt::MouseButton _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1, _t2);
}
QT_WARNING_POP
