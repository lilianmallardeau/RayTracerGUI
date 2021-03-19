#ifndef LIGHTPROPERTIESWIDGET_H
#define LIGHTPROPERTIESWIDGET_H

#include <Light.h>
#include "propertieseditorwidget.h"
#include "vectorentrywidget.h"
#include "floatedit.h"

class LightPropertiesWidget : public PropertiesEditorWidget
{
    Q_OBJECT
public:
    explicit LightPropertiesWidget(Light* light, QWidget *parent = nullptr);
    void updateMaterials(QStandardItemModel *) override {};

private:
    VectorEntryWidget* position;
    FloatEdit* intensity;
    Light* light;

private slots:
    void updateObject();

};

#endif // LIGHTPROPERTIESWIDGET_H
