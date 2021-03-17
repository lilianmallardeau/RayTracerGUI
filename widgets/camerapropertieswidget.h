#ifndef CAMERAPROPERTIESWIDGET_H
#define CAMERAPROPERTIESWIDGET_H

#include <QWidget>
#include <QFormLayout>
#include "vectorentrywidget.h"

class CameraPropertiesWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CameraPropertiesWidget(QWidget *parent = nullptr);

private:
    VectorEntryWidget position, direction, up, right;
    FloatEdit screen_dist, width, height;

    QFormLayout *layout;

signals:

};

#endif // CAMERAPROPERTIESWIDGET_H
