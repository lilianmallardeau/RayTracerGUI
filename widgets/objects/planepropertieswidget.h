#ifndef PLANEPROPERTIESWIDGET_H
#define PLANEPROPERTIESWIDGET_H

#include <Plane.h>
#include "../propertieseditorwidget.h"
#include "../vectorentrywidget.h"
#include "../floatedit.h"

class PlanePropertiesWidget : public PropertiesEditorWidget
{
    Q_OBJECT
public:
    explicit PlanePropertiesWidget(Plane* plane, QWidget *parent = nullptr);

private:
    VectorEntryWidget *point, *normal;
    Plane* obj;

private slots:
    void updateObject();

};

#endif // PLANEPROPERTIESWIDGET_H
