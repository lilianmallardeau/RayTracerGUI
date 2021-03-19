#include "quadpropertieswidget.h"

QuadPropertiesWidget::QuadPropertiesWidget(Quad* quad, QWidget *parent) : PropertiesEditorWidget(parent)
{
    obj = quad;
    origin = new VectorEntryWidget(quad->origin);
    width = new VectorEntryWidget(quad->width);
    height = new VectorEntryWidget(quad->height);
    layout->addRow("Origin", origin);
    layout->addRow("Width", width);
    layout->addRow("Height", height);

    connect(origin, SIGNAL(modified(Vector3D)), this, SLOT(updateObject()));
    connect(width, SIGNAL(modified(Vector3D)), this, SLOT(updateObject()));
    connect(height, SIGNAL(modified(Vector3D)), this, SLOT(updateObject()));
}

void QuadPropertiesWidget::updateMaterials(QStandardItemModel *materialModel) {
    materials->setModel(materialModel);
}

void QuadPropertiesWidget::updateObject() {
    obj->origin = origin->toVector();
    obj->width = width->toVector();
    obj->height = height->toVector();
    emit objectModified();
}
