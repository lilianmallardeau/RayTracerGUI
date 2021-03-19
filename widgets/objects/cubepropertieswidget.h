#ifndef CUBEPROPERTIESWIDGET_H
#define CUBEPROPERTIESWIDGET_H

#include <Cube.h>
#include "../propertieseditorwidget.h"
#include "../vectorentrywidget.h"
#include "../floatedit.h"
#include <QComboBox>

class CubePropertiesWidget : public PropertiesEditorWidget
{
    Q_OBJECT
public:
    explicit CubePropertiesWidget(Cube* cube, QStandardItemModel *materialModel, QWidget *parent = nullptr);

private:
    VectorEntryWidget *origin, *width, *height, *length;
    QComboBox *materials;
    Cube* obj;

private slots:
    void updateObject();

};

#endif // CUBEPROPERTIESWIDGET_H
