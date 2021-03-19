#ifndef CAMERAPROPERTIESWIDGET_H
#define CAMERAPROPERTIESWIDGET_H

#include <Camera.h>
#include "propertieseditorwidget.h"
#include "vectorentrywidget.h"
#include "floatedit.h"

class CameraPropertiesWidget : public PropertiesEditorWidget
{
    Q_OBJECT
public:
    explicit CameraPropertiesWidget(Camera* cam, QWidget *parent = nullptr);
    void updateMaterials(QStandardItemModel *) override {};

private:
    VectorEntryWidget *position, *direction, *up, *right;
    FloatEdit *screen_dist, *width, *height;
    Camera* cam;

private slots:
    void updateObject();

};

#endif // CAMERAPROPERTIESWIDGET_H
