#include "spherepropertieswidget.h"

SpherePropertiesWidget::SpherePropertiesWidget(Sphere* sphere, QWidget *parent) : PropertiesEditorWidget(parent)
{
    obj = sphere;
    center = new VectorEntryWidget(sphere->center);
    radius = new FloatEdit(sphere->radius);
    materials = new QComboBox(this);
    layout->addRow("Position", center);
    layout->addRow("Radius", radius);
    layout->addRow("Material", materials);

    connect(center, SIGNAL(modified(Vector3D)), this, SLOT(updateObject()));
    connect(radius, SIGNAL(editingFinished()), this, SLOT(updateObject()));
}

void SpherePropertiesWidget::updateMaterials(QStandardItemModel *materialModel) {
    materials->setModel(materialModel);
}

void SpherePropertiesWidget::updateObject() {
    obj->center = center->toVector();
    obj->radius = radius->getValue();
    emit objectModified();
}
