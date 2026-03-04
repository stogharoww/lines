/****************************************************************************
** Meta object code from reading C++ file 'plotapi.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../plotapi.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plotapi.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN7PlotAPIE_t {};
} // unnamed namespace

template <> constexpr inline auto PlotAPI::qt_create_metaobjectdata<qt_meta_tag_ZN7PlotAPIE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PlotAPI",
        "bottomHomeClicked",
        "",
        "moveEvent",
        "QPointF",
        "delta",
        "movingMouse",
        "pos",
        "leaved",
        "leav",
        "wheel",
        "localPos",
        "btmPunktireClicked",
        "btmPointClicked",
        "btmLineClicked",
        "btmAddingPoints",
        "btmCleanAll",
        "btmReadFile",
        "btmSaveToPng",
        "editPoints",
        "Qt::MouseButton",
        "button",
        "emptyFuncs"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'bottomHomeClicked'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'moveEvent'
        QtMocHelpers::SlotData<void(QPointF)>(3, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 4, 5 },
        }}),
        // Slot 'movingMouse'
        QtMocHelpers::SlotData<void(QPointF)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 4, 7 },
        }}),
        // Slot 'leaved'
        QtMocHelpers::SlotData<void(bool)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 9 },
        }}),
        // Slot 'wheel'
        QtMocHelpers::SlotData<void(QPointF, int)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 4, 11 }, { QMetaType::Int, 5 },
        }}),
        // Slot 'btmPunktireClicked'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'btmPointClicked'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'btmLineClicked'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'btmAddingPoints'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'btmCleanAll'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'btmReadFile'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'btmSaveToPng'
        QtMocHelpers::SlotData<void()>(18, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'editPoints'
        QtMocHelpers::SlotData<void(QPointF, Qt::MouseButton)>(19, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 4, 7 }, { 0x80000000 | 20, 21 },
        }}),
        // Slot 'emptyFuncs'
        QtMocHelpers::SlotData<void()>(22, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PlotAPI, qt_meta_tag_ZN7PlotAPIE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PlotAPI::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsView::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PlotAPIE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PlotAPIE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN7PlotAPIE_t>.metaTypes,
    nullptr
} };

void PlotAPI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PlotAPI *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->bottomHomeClicked(); break;
        case 1: _t->moveEvent((*reinterpret_cast<std::add_pointer_t<QPointF>>(_a[1]))); break;
        case 2: _t->movingMouse((*reinterpret_cast<std::add_pointer_t<QPointF>>(_a[1]))); break;
        case 3: _t->leaved((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 4: _t->wheel((*reinterpret_cast<std::add_pointer_t<QPointF>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2]))); break;
        case 5: _t->btmPunktireClicked(); break;
        case 6: _t->btmPointClicked(); break;
        case 7: _t->btmLineClicked(); break;
        case 8: _t->btmAddingPoints(); break;
        case 9: _t->btmCleanAll(); break;
        case 10: _t->btmReadFile(); break;
        case 11: _t->btmSaveToPng(); break;
        case 12: _t->editPoints((*reinterpret_cast<std::add_pointer_t<QPointF>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<Qt::MouseButton>>(_a[2]))); break;
        case 13: _t->emptyFuncs(); break;
        default: ;
        }
    }
}

const QMetaObject *PlotAPI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlotAPI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PlotAPIE_t>.strings))
        return static_cast<void*>(this);
    return QGraphicsView::qt_metacast(_clname);
}

int PlotAPI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
