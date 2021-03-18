#ifndef QSCENEOBJECT_H
#define QSCENEOBJECT_H

#include "Object.h"
#include "Camera.h"

enum ObjectType {
    CAMERA,
    LIGHT,
    PLANE,
    QUAD,
    CUBE,
    SPHERE
};

class QSceneObject
{
public:
    QSceneObject() = default;
    ~QSceneObject() = default;
    QSceneObject(const QSceneObject &) = default;
    QSceneObject &operator=(const QSceneObject &) = default;
    QSceneObject(Object *, ObjectType type);
    QSceneObject(ObjectType type);

    ObjectType type;


private:
    Object *obj = nullptr;

};


#endif // QSCENEOBJECT_H
