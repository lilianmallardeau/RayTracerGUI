#include "camerapropertieswidget.h"

CameraPropertiesWidget::CameraPropertiesWidget(QWidget *parent) : PropertiesEditorWidget(parent)
{
    layout->addRow("Position", &position);
    layout->addRow("Direction", &direction);
    layout->addRow("Up", &up);
    layout->addRow("Right", &right);
    layout->addRow("Distance to screen", &screen_dist);
    layout->addRow("Width", &width);
    layout->addRow("Height", &height);
}
