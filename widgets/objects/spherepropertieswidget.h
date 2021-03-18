#ifndef SPHEREPROPERTIESWIDGET_H
#define SPHEREPROPERTIESWIDGET_H

#include "../propertieseditorwidget.h"
#include "../vectorentrywidget.h"
#include "../floatedit.h"

class SpherePropertiesWidget : public PropertiesEditorWidget
{
    Q_OBJECT
public:
    explicit SpherePropertiesWidget(QWidget *parent = nullptr);

private:
    VectorEntryWidget position;
    FloatEdit radius;

signals:

};

#endif // SPHEREPROPERTIESWIDGET_H
