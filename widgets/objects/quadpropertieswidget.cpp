#include "quadpropertieswidget.h"

QuadPropertiesWidget::QuadPropertiesWidget(QWidget *parent) : PropertiesEditorWidget(parent)
{
    layout->addRow("Origin", &origin);
    layout->addRow("Width", &width);
    layout->addRow("Height", &height);
}
