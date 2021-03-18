#ifndef QSCENEOBJECT_H
#define QSCENEOBJECT_H

#include "Object.h"
#include "Camera.h"
#include <QMetaType>
#include <QDebug>

enum ObjectTyype {
CAMERA,
LIGHT,
OBJECT
};

class QSceneObject
{
public:
    QSceneObject() = default;
    ~QSceneObject() = default;
    QSceneObject(const QSceneObject &) = default;
    QSceneObject &operator=(const QSceneObject &) = default;
    QSceneObject(Object *);
    QSceneObject(ObjectTyype);

    friend QDebug operator<<(QDebug dbg, const QSceneObject &);

    ObjectTyype type;


private:
    Object *obj = nullptr;

};

Q_DECLARE_METATYPE(QSceneObject);


#endif // QSCENEOBJECT_H
