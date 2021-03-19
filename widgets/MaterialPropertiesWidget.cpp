//
// Created by lilian on 19/03/2021.
//

#include "MaterialPropertiesWidget.h"

MaterialPropertiesWidget::MaterialPropertiesWidget(Material *material, QWidget *parent) : PropertiesEditorWidget(parent)
{
    this->material = material;
    colorDialog = new QColorDialog();
    //colorDialog->setOption(QColorDialog::ShowAlphaChannel);
    setColorButton = new QPushButton("Set color");
    connect(setColorButton, SIGNAL(clicked(bool)), colorDialog, SLOT(open()));
    connect(colorDialog, SIGNAL(colorSelected(const QColor &)), this, SLOT(updateButtonColor(const QColor &)));
    if (autoUpdateOnSelect)
        connect(colorDialog, SIGNAL(currentColorChanged(const QColor &)), this, SLOT(updateObject(const QColor &)));
    else
        connect(colorDialog, SIGNAL(colorSelected(const QColor &)), this, SLOT(updateObject(const QColor &)));

    name = new QLineEdit(QString::fromStdString(material->name));
    shininess = new FloatEdit(material->shininess);
    alpha = new FloatEdit(material->alpha);
    Ka = new FloatEdit(material->Ka);
    Kd = new FloatEdit(material->Kd);
    Ks = new FloatEdit(material->Ks);
    layout->addRow("Material name", name);
    layout->addRow("Color", setColorButton);
    layout->addRow("Shininess", shininess);
    layout->addRow("alpha", alpha);
    layout->addRow("Ka", Ka);
    layout->addRow("Kd", Kd);
    layout->addRow("Ks", Ks);

    connect(name, SIGNAL(editingFinished()), this, SLOT(updateObject()));
    connect(shininess, SIGNAL(editingFinished()), this, SLOT(updateObject()));
    connect(alpha, SIGNAL(editingFinished()), this, SLOT(updateObject()));
    connect(Ka, SIGNAL(editingFinished()), this, SLOT(updateObject()));
    connect(Kd, SIGNAL(editingFinished()), this, SLOT(updateObject()));
    connect(Ks, SIGNAL(editingFinished()), this, SLOT(updateObject()));

    updateButtonColor(QColor(material->color.r, material->color.g, material->color.b));
}

void MaterialPropertiesWidget::updateObject(const QColor & color) {
    material->name = name->text().toStdString();
    if (color != nullptr)
        color.getRgb(reinterpret_cast<int *>(&material->color.r),
                 reinterpret_cast<int *>(&material->color.g),
                 reinterpret_cast<int *>(&material->color.b));
    material->shininess = shininess->getValue();
    material->alpha = alpha->getValue();
    material->Ka = Ka->getValue();
    material->Kd = Kd->getValue();
    material->Ks = Ks->getValue();
    emit objectModified();
}

void MaterialPropertiesWidget::updateButtonColor(const QColor & color) {
    QPalette pal = setColorButton->palette();
    pal.setColor(QPalette::Button, color);
    setColorButton->setAutoFillBackground(true);
    setColorButton->setPalette(pal);
    setColorButton->update();
}
