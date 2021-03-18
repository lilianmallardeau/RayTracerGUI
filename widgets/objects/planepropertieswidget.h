#ifndef PLANEPROPERTIESWIDGET_H
#define PLANEPROPERTIESWIDGET_H

#include "../propertieseditorwidget.h"
#include "../vectorentrywidget.h"
#include "../floatedit.h"

class PlanePropertiesWidget : public PropertiesEditorWidget
{
    Q_OBJECT
public:
    explicit PlanePropertiesWidget(QWidget *parent = nullptr);

private:
    VectorEntryWidget point, normal;

signals:

};

#endif // PLANEPROPERTIESWIDGET_H
