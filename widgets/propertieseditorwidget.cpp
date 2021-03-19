#include "propertieseditorwidget.h"

PropertiesEditorWidget::PropertiesEditorWidget(QWidget *parent, QStandardItemModel *materialModel) : QWidget(parent), materialModel(materialModel)
{
    layout = new QFormLayout(this);
}
