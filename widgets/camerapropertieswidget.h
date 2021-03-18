#ifndef CAMERAPROPERTIESWIDGET_H
#define CAMERAPROPERTIESWIDGET_H

#include "propertieseditorwidget.h"
#include "vectorentrywidget.h"
#include "floatedit.h"

class CameraPropertiesWidget : public PropertiesEditorWidget
{
    Q_OBJECT
public:
    explicit CameraPropertiesWidget(QWidget *parent = nullptr);

private:
    VectorEntryWidget position, direction, up, right;
    FloatEdit screen_dist, width, height;

signals:

};

#endif // CAMERAPROPERTIESWIDGET_H
