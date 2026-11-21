/****************************************************************************
** Meta object code from reading C++ file 'yasumiapp.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/yasumiapp.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'yasumiapp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.12.0. It"
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
struct qt_meta_tag_ZN9YasumiAppE_t {};
} // unnamed namespace

template <> constexpr inline auto YasumiApp::qt_create_metaobjectdata<qt_meta_tag_ZN9YasumiAppE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "YasumiApp",
        "stateChanged",
        "",
        "remainingChanged",
        "intervalChanged",
        "durationChanged",
        "enabledChanged",
        "showOverlay",
        "hideOverlay",
        "tick",
        "onIpcConnection",
        "breakNow",
        "endBreak",
        "pause",
        "resume",
        "togglePause",
        "state",
        "remaining",
        "interval",
        "duration",
        "enabled",
        "breaking",
        "countdown",
        "progress"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'stateChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'remainingChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'intervalChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'durationChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'enabledChanged'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'showOverlay'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'hideOverlay'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'tick'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onIpcConnection'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Method 'breakNow'
        QtMocHelpers::MethodData<void()>(11, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'endBreak'
        QtMocHelpers::MethodData<void()>(12, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'pause'
        QtMocHelpers::MethodData<void()>(13, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'resume'
        QtMocHelpers::MethodData<void()>(14, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'togglePause'
        QtMocHelpers::MethodData<void()>(15, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'state'
        QtMocHelpers::PropertyData<QString>(16, QMetaType::QString, QMC::DefaultPropertyFlags, 0),
        // property 'remaining'
        QtMocHelpers::PropertyData<int>(17, QMetaType::Int, QMC::DefaultPropertyFlags, 1),
        // property 'interval'
        QtMocHelpers::PropertyData<int>(18, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 2),
        // property 'duration'
        QtMocHelpers::PropertyData<int>(19, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 3),
        // property 'enabled'
        QtMocHelpers::PropertyData<bool>(20, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 4),
        // property 'breaking'
        QtMocHelpers::PropertyData<bool>(21, QMetaType::Bool, QMC::DefaultPropertyFlags, 0),
        // property 'countdown'
        QtMocHelpers::PropertyData<QString>(22, QMetaType::QString, QMC::DefaultPropertyFlags, 1),
        // property 'progress'
        QtMocHelpers::PropertyData<double>(23, QMetaType::Double, QMC::DefaultPropertyFlags, 1),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<YasumiApp, qt_meta_tag_ZN9YasumiAppE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject YasumiApp::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9YasumiAppE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9YasumiAppE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN9YasumiAppE_t>.metaTypes,
    nullptr
} };

void YasumiApp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<YasumiApp *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->stateChanged(); break;
        case 1: _t->remainingChanged(); break;
        case 2: _t->intervalChanged(); break;
        case 3: _t->durationChanged(); break;
        case 4: _t->enabledChanged(); break;
        case 5: _t->showOverlay(); break;
        case 6: _t->hideOverlay(); break;
        case 7: _t->tick(); break;
        case 8: _t->onIpcConnection(); break;
        case 9: _t->breakNow(); break;
        case 10: _t->endBreak(); break;
        case 11: _t->pause(); break;
        case 12: _t->resume(); break;
        case 13: _t->togglePause(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (YasumiApp::*)()>(_a, &YasumiApp::stateChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (YasumiApp::*)()>(_a, &YasumiApp::remainingChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (YasumiApp::*)()>(_a, &YasumiApp::intervalChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (YasumiApp::*)()>(_a, &YasumiApp::durationChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (YasumiApp::*)()>(_a, &YasumiApp::enabledChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (YasumiApp::*)()>(_a, &YasumiApp::showOverlay, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (YasumiApp::*)()>(_a, &YasumiApp::hideOverlay, 6))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->state(); break;
        case 1: *reinterpret_cast<int*>(_v) = _t->remaining(); break;
        case 2: *reinterpret_cast<int*>(_v) = _t->interval(); break;
        case 3: *reinterpret_cast<int*>(_v) = _t->duration(); break;
        case 4: *reinterpret_cast<bool*>(_v) = _t->enabled(); break;
        case 5: *reinterpret_cast<bool*>(_v) = _t->breaking(); break;
        case 6: *reinterpret_cast<QString*>(_v) = _t->countdown(); break;
        case 7: *reinterpret_cast<double*>(_v) = _t->progress(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 2: _t->setInterval(*reinterpret_cast<int*>(_v)); break;
        case 3: _t->setDuration(*reinterpret_cast<int*>(_v)); break;
        case 4: _t->setEnabled(*reinterpret_cast<bool*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *YasumiApp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *YasumiApp::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9YasumiAppE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int YasumiApp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void YasumiApp::stateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void YasumiApp::remainingChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void YasumiApp::intervalChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void YasumiApp::durationChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void YasumiApp::enabledChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void YasumiApp::showOverlay()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void YasumiApp::hideOverlay()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
