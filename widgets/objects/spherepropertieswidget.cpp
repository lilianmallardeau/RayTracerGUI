#include "spherepropertieswidget.h"

SpherePropertiesWidget::SpherePropertiesWidget(Sphere* sphere, QStandardItemModel *materialModel, QWidget *parent) : PropertiesEditorWidget(parent, materialModel)
{
    obj = sphere;
    center = new VectorEntryWidget(sphere->center);
    radius = new FloatEdit(sphere->radius);
    materials = new QComboBox(this);
    materials->setModel(materialModel);
    layout->addRow("Position", center);
    layout->addRow("Radius", radius);
    layout->addRow("Material", materials);

    connect(center, SIGNAL(modified(Vector3D)), this, SLOT(updateObject()));
    connect(radius, SIGNAL(editingFinished()), this, SLOT(updateObject()));
}

void SpherePropertiesWidget::updateObject() {
    obj->center = center->toVector();
    obj->radius = radius->getValue();
    emit objectModified();
}
