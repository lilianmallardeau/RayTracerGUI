#include "qsceneobject.h"

QSceneObject::QSceneObject(Object *obj, ObjectType type) : obj(obj), type(type)
{}

QSceneObject::QSceneObject(ObjectType type) : type(type)
{}
