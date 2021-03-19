#include "spherepropertieswidget.h"

SpherePropertiesWidget::SpherePropertiesWidget(Sphere* sphere, QWidget *parent) : PropertiesEditorWidget(parent)
{
    obj = sphere;
    center = new VectorEntryWidget(sphere->center);
    radius = new FloatEdit(sphere->radius);
    layout->addRow("Position", center);
    layout->addRow("Radius", radius);

    connect(center, SIGNAL(modified(Vector3D)), this, SLOT(updateObject()));
    connect(radius, SIGNAL(editingFinished()), this, SLOT(updateObject()));
}

void SpherePropertiesWidget::updateObject() {
    obj->center = center->toVector();
    obj->radius = radius->getValue();
    emit objectModified();
}
