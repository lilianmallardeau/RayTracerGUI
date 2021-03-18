#ifndef LIGHTPROPERTIESWIDGET_H
#define LIGHTPROPERTIESWIDGET_H

#include "propertieseditorwidget.h"
#include "vectorentrywidget.h"
#include "floatedit.h"

class LightPropertiesWidget : public PropertiesEditorWidget
{
    Q_OBJECT
public:
    explicit LightPropertiesWidget(QWidget *parent = nullptr);

private:
    VectorEntryWidget position;
    FloatEdit intensity;

signals:

};

#endif // LIGHTPROPERTIESWIDGET_H
