#include "planepropertieswidget.h"

PlanePropertiesWidget::PlanePropertiesWidget(Plane* plane, QStandardItemModel *materialModel, QWidget *parent) : ObjectPropertiesWidget(plane, materialModel, parent), plane(plane)
{
    point = new VectorEntryWidget(plane->point);
    normal = new VectorEntryWidget(plane->getNormal());
    layout->addRow("Point", point);
    layout->addRow("Normal", normal);

    connect(point, SIGNAL(modified(Vector3D)), this, SLOT(updateObject()));
    connect(normal, SIGNAL(modified(Vector3D)), this, SLOT(updateObject()));
}

void PlanePropertiesWidget::updateObject() {
    plane->point = point->toVector();
    plane->setNormal(normal->toVector());
    emit objectModified();
}
