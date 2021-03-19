//
// Created by lilian on 19/03/2021.
//

#ifndef MATERIALPROPERTIESWIDGET_H
#define MATERIALPROPERTIESWIDGET_H

#include <QColorDialog>
#include <QPushButton>
#include "Material.h"
#include "propertieseditorwidget.h"
#include "vectorentrywidget.h"
#include "floatedit.h"

class MaterialPropertiesWidget : public PropertiesEditorWidget
{
    Q_OBJECT
public:
    explicit MaterialPropertiesWidget(Material* material, QStandardItemModel *materialModel, QWidget *parent = nullptr);

private:
    bool autoUpdateOnSelect = false;

    QColorDialog *colorDialog;
    QPushButton *setColorButton;
    FloatEdit *shininess, *alpha, *Ka, *Kd, *Ks;
    Material *material;

private slots:
    void updateObject(const QColor & = nullptr);
    void updateButtonColor(const QColor &);

};

#endif // MATERIALPROPERTIESWIDGET_H
