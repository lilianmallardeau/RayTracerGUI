#include "planepropertieswidget.h"

PlanePropertiesWidget::PlanePropertiesWidget(Plane* plane, QStandardItemModel *materialModel, QWidget *parent) : PropertiesEditorWidget(parent, materialModel)
{
    obj = plane;
    point = new VectorEntryWidget(plane->point);
    normal = new VectorEntryWidget(plane->getNormal());
    materials = new QComboBox(this);
    materials->setModel(materialModel);
    layout->addRow("Point", point);
    layout->addRow("Normal", normal);
    layout->addRow("Material", materials);

    connect(point, SIGNAL(modified(Vector3D)), this, SLOT(updateObject()));
    connect(normal, SIGNAL(modified(Vector3D)), this, SLOT(updateObject()));
}

void PlanePropertiesWidget::updateObject() {
    obj->point = point->toVector();
    obj->setNormal(normal->toVector());
    emit objectModified();
}
