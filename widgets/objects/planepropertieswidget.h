#ifndef PLANEPROPERTIESWIDGET_H
#define PLANEPROPERTIESWIDGET_H

#include <Plane.h>
#include "ObjectPropertiesWidget.h"
#include "../vectorentrywidget.h"
#include "../floatedit.h"

class PlanePropertiesWidget : public ObjectPropertiesWidget
{
    Q_OBJECT
public:
    explicit PlanePropertiesWidget(Plane* plane, QStandardItemModel *materialModel, QWidget *parent = nullptr);

private:
    VectorEntryWidget *point, *normal;
    Plane* plane;

private slots:
    void updateObject() override;

};

#endif // PLANEPROPERTIESWIDGET_H
