#include "planepropertieswidget.h"

PlanePropertiesWidget::PlanePropertiesWidget(Plane* plane, QWidget *parent) : PropertiesEditorWidget(parent)
{
    obj = plane;
    point = new VectorEntryWidget(plane->point);
    normal = new VectorEntryWidget(plane->getNormal());
    layout->addRow("Point", point);
    layout->addRow("Normal", normal);

    connect(point, SIGNAL(modified(Vector3D)), this, SLOT(updateObject()));
    connect(normal, SIGNAL(modified(Vector3D)), this, SLOT(updateObject()));
}

void PlanePropertiesWidget::updateMaterials(QStandardItemModel *materialModel) {
    materials->setModel(materialModel);
}

void PlanePropertiesWidget::updateObject() {
    obj->point = point->toVector();
    obj->setNormal(normal->toVector());
    emit objectModified();
}
