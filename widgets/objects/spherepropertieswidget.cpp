#include "spherepropertieswidget.h"

SpherePropertiesWidget::SpherePropertiesWidget(Sphere* sphere, QStandardItemModel *materialModel, QWidget *parent) : ObjectPropertiesWidget(sphere, materialModel, parent), sphere(sphere)
{
    center = new VectorEntryWidget(sphere->center);
    radius = new FloatEdit(sphere->radius);
    radius->setMinimum(0);
    layout->addRow("Position", center);
    layout->addRow("Radius", radius);

    connect(center, SIGNAL(modified(Vector3D)), this, SLOT(updateObject()));
    connect(radius, SIGNAL(valueChanged(double)), this, SLOT(updateObject()));
}

void SpherePropertiesWidget::updateObject() {
    sphere->center = center->toVector();
    sphere->radius = radius->getValue();
    emit objectModified();
}
