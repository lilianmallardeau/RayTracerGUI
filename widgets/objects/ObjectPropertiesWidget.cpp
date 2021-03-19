//
// Created by lilian on 19/03/2021.
//

#include "ObjectPropertiesWidget.h"

ObjectPropertiesWidget::ObjectPropertiesWidget(Object* obj, QStandardItemModel *materialModel, QWidget *parent) : PropertiesEditorWidget(parent), obj(obj), materialModel(materialModel)
{
    name = new QLineEdit(QString::fromStdString(obj->name));
    material = new QComboBox();
    material->setModel(materialModel);
    material->setCurrentText(QString::fromStdString(obj->material.name));
    layout->addRow("Object name", name);
    layout->addRow("Material", material);

    connect(name, SIGNAL(editingFinished()), this, SLOT(updateObjectName()));
    connect(material, SIGNAL(activated(int)), this, SLOT(updateObjectMaterial(int)));
}

void ObjectPropertiesWidget::updateObjectName() {
    obj->name = name->text().toStdString();
    emit objectNameChanged();
}

void ObjectPropertiesWidget::updateObjectMaterial(int index) {
    // FIXME material stored not as  pointer, so updating material doesn't update scene
    obj->material = *(qobject_cast<QStandardItemModel *>(material->model())->item(index)->data().value<Material *>());
    emit objectModified();
}
