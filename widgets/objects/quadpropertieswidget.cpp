#include "quadpropertieswidget.h"
#include <QDebug>

QuadPropertiesWidget::QuadPropertiesWidget(Quad* quad, QStandardItemModel *materialModel, QWidget *parent) : PropertiesEditorWidget(parent, materialModel)
{
    obj = quad;
    origin = new VectorEntryWidget(quad->origin);
    width = new VectorEntryWidget(quad->width);
    height = new VectorEntryWidget(quad->height);
    materials = new QComboBox(this);
    materials->setModel(this->materialModel);
    layout->addRow("Origin", origin);
    layout->addRow("Width", width);
    layout->addRow("Height", height);
    layout->addRow("Material", materials);

    connect(origin, SIGNAL(modified(Vector3D)), this, SLOT(updateObject()));
    connect(width, SIGNAL(modified(Vector3D)), this, SLOT(updateObject()));
    connect(height, SIGNAL(modified(Vector3D)), this, SLOT(updateObject()));
    connect(materials, SIGNAL(currentIndexChanged(int)), this, SLOT(updateObjectMaterial(int)));
}

void QuadPropertiesWidget::updateObject() {
    obj->origin = origin->toVector();
    obj->width = width->toVector();
    obj->height = height->toVector();
    emit objectModified();
}

void QuadPropertiesWidget::updateObjectMaterial(int index) {
    // FIXME material stored not as  pointer, so updating material doesn't update scene
    obj->material = *(qobject_cast<QStandardItemModel *>(materials->model())->item(index)->data().value<Material *>());
    emit objectModified();
}
