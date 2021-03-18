#include "spherepropertieswidget.h"

SpherePropertiesWidget::SpherePropertiesWidget(QWidget *parent) : PropertiesEditorWidget(parent)
{
    layout->addRow("Position", &position);
    layout->addRow("Radius", &radius);
}
