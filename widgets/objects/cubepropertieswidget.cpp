#include "cubepropertieswidget.h"

CubePropertiesWidget::CubePropertiesWidget(Cube* cube, QStandardItemModel *materialModel, QWidget *parent) : ObjectPropertiesWidget(cube, materialModel, parent), cube(cube)
{
    origin = new VectorEntryWidget(cube->origin);
    width = new VectorEntryWidget(cube->width);
    height = new VectorEntryWidget(cube->height);
    length = new VectorEntryWidget(cube->length);
    layout->addRow("Origin", origin);
    layout->addRow("Width", width);
    layout->addRow("Height", height);
    layout->addRow("Length", length);

    connect(origin, SIGNAL(modified(Vector3D)), this, SLOT(updateObject()));
    connect(width, SIGNAL(modified(Vector3D)), this, SLOT(updateObject()));
    connect(height, SIGNAL(modified(Vector3D)), this, SLOT(updateObject()));
    connect(length, SIGNAL(modified(Vector3D)), this, SLOT(updateObject()));
}
void CubePropertiesWidget::updateObject() {
    cube->origin = origin->toVector();
    cube->width = width->toVector();
    cube->height = height->toVector();
    cube->length = length->toVector();
    emit objectModified();
}
