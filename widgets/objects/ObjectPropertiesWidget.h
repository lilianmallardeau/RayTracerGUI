//
// Created by lilian on 19/03/2021.
//

#ifndef OBJECTPROPERTIESWIDGET_H
#define OBJECTPROPERTIESWIDGET_H

#include <QLineEdit>
#include <QComboBox>
#include <Object.h>
#include "../propertieseditorwidget.h"

class ObjectPropertiesWidget : public PropertiesEditorWidget
{
    Q_OBJECT
public:
    explicit ObjectPropertiesWidget(Object* obj, QStandardItemModel *materialModel, QWidget *parent = nullptr);

private:
    Object* obj;
    QStandardItemModel *materialModel;
    QLineEdit *name;
    QComboBox *material;

signals:
    void objectNameChanged();

private slots:
    virtual void updateObject() = 0;
    virtual void updateObjectName();
    void updateObjectMaterial(int index);

};


#endif // OBJECTPROPERTIESWIDGET_H
