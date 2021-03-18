#include "planepropertieswidget.h"

PlanePropertiesWidget::PlanePropertiesWidget(QWidget *parent) : PropertiesEditorWidget(parent)
{
    layout->addRow("Point", &point);
    layout->addRow("Normal", &normal);
}
