#include "cubepropertieswidget.h"

CubePropertiesWidget::CubePropertiesWidget(QWidget *parent) : PropertiesEditorWidget(parent)
{
    layout->addRow("Origin", &origin);
    layout->addRow("Width", &width);
    layout->addRow("Height", &height);
    layout->addRow("Length", &length);
}
