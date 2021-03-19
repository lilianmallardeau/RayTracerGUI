#ifndef CUBEPROPERTIESWIDGET_H
#define CUBEPROPERTIESWIDGET_H

#include <Cube.h>
#include "ObjectPropertiesWidget.h"
#include "../vectorentrywidget.h"
#include "../floatedit.h"

class CubePropertiesWidget : public ObjectPropertiesWidget
{
    Q_OBJECT
public:
    explicit CubePropertiesWidget(Cube* cube, QStandardItemModel *materialModel, QWidget *parent = nullptr);

private:
    VectorEntryWidget *origin, *width, *height, *length;
    Cube* cube;

private slots:
    void updateObject() override;

};

#endif // CUBEPROPERTIESWIDGET_H
