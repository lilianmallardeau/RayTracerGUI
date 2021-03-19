#include "cubepropertieswidget.h"

CubePropertiesWidget::CubePropertiesWidget(Cube* cube, QStandardItemModel *materialModel, QWidget *parent) : PropertiesEditorWidget(parent, materialModel)
{
    obj = cube;
    origin = new VectorEntryWidget(cube->origin);
    width = new VectorEntryWidget(cube->width);
    height = new VectorEntryWidget(cube->height);
    length = new VectorEntryWidget(cube->length);
    materials = new QComboBox(this);
    materials->setModel(materialModel);
    layout->addRow("Origin", origin);
    layout->addRow("Width", width);
    layout->addRow("Height", height);
    layout->addRow("Length", length);
    layout->addRow("Material", materials);

    connect(origin, SIGNAL(modified(Vector3D)), this, SLOT(updateObject()));
    connect(width, SIGNAL(modified(Vector3D)), this, SLOT(updateObject()));
    connect(height, SIGNAL(modified(Vector3D)), this, SLOT(updateObject()));
    connect(length, SIGNAL(modified(Vector3D)), this, SLOT(updateObject()));
}
void CubePropertiesWidget::updateObject() {
    obj->origin = origin->toVector();
    obj->width = width->toVector();
    obj->height = height->toVector();
    obj->length = length->toVector();
    emit objectModified();
}
