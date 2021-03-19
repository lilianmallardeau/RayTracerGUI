#include "lightpropertieswidget.h"

LightPropertiesWidget::LightPropertiesWidget(Light* light, QWidget *parent) : PropertiesEditorWidget(parent)
{
    this->light = light;
    position = new VectorEntryWidget(light->position);
    intensity = new FloatEdit(light->intensity);
    layout->addRow("Position", position);
    layout->addRow("Intensity", intensity);

    connect(position, SIGNAL(modified(Vector3D)), this, SLOT(updateObject()));
    connect(intensity, SIGNAL(editingFinished()), this, SLOT(updateObject()));
}

void LightPropertiesWidget::updateObject() {
    light->position = position->toVector();
    light->intensity = intensity->getValue();
    emit objectModified();
}
