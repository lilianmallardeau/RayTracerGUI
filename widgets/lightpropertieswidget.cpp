#include "lightpropertieswidget.h"

LightPropertiesWidget::LightPropertiesWidget(QWidget *parent) : PropertiesEditorWidget(parent)
{
    layout->addRow("Position", &position);
    layout->addRow("Intensity", &intensity);
}
