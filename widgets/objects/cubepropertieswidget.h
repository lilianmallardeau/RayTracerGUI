#ifndef CUBEPROPERTIESWIDGET_H
#define CUBEPROPERTIESWIDGET_H

#include "../propertieseditorwidget.h"
#include "../vectorentrywidget.h"
#include "../floatedit.h"

class CubePropertiesWidget : public PropertiesEditorWidget
{
    Q_OBJECT
public:
    explicit CubePropertiesWidget(QWidget *parent = nullptr);

private:
    VectorEntryWidget origin, width, height, length;

signals:

};

#endif // CUBEPROPERTIESWIDGET_H
