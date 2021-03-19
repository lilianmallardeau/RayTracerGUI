#ifndef SPHEREPROPERTIESWIDGET_H
#define SPHEREPROPERTIESWIDGET_H

#include <Sphere.h>
#include "ObjectPropertiesWidget.h"
#include "../vectorentrywidget.h"
#include "../floatedit.h"

class SpherePropertiesWidget : public ObjectPropertiesWidget
{
    Q_OBJECT
public:
    explicit SpherePropertiesWidget(Sphere* sphere, QStandardItemModel *materialModel, QWidget *parent = nullptr);

private:
    VectorEntryWidget *center;
    FloatEdit *radius;
    Sphere* sphere;

private slots:
    void updateObject() override;

};

#endif // SPHEREPROPERTIESWIDGET_H
