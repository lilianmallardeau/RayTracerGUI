#include "qsceneobject.h"

QSceneObject::QSceneObject(Object *obj) : obj(obj), type(ObjectTyype::OBJECT)
{}

QSceneObject::QSceneObject(ObjectTyype type) : type(type)
{}

QDebug operator<<(QDebug dbg, const QSceneObject &obj) {
    switch (obj.type) {
        case ObjectTyype::CAMERA:
            dbg.space() << "Type(camera)";
            break;
        case ObjectTyype::LIGHT:
            dbg.space() << "Type(light)";
            break;
        case ObjectTyype::OBJECT:
            dbg.space() << "Type(object)";
            break;
    }
    return dbg.maybeSpace();
}
