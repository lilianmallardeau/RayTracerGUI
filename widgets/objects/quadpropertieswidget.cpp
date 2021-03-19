#include "quadpropertieswidget.h"

QuadPropertiesWidget::QuadPropertiesWidget(Quad* quad, QStandardItemModel *materialModel, QWidget *parent) : ObjectPropertiesWidget(quad, materialModel, parent), quad(quad)
{
    origin = new VectorEntryWidget(quad->origin);
    width = new VectorEntryWidget(quad->width);
    height = new VectorEntryWidget(quad->height);
    layout->addRow("Origin", origin);
    layout->addRow("Width", width);
    layout->addRow("Height", height);

    connect(origin, SIGNAL(modified(Vector3D)), this, SLOT(updateObject()));
    connect(width, SIGNAL(modified(Vector3D)), this, SLOT(updateObject()));
    connect(height, SIGNAL(modified(Vector3D)), this, SLOT(updateObject()));
}

void QuadPropertiesWidget::updateObject() {
    quad->origin = origin->toVector();
    quad->width = width->toVector();
    quad->height = height->toVector();
    emit objectModified();
}