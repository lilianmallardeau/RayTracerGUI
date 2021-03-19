#include "camerapropertieswidget.h"

CameraPropertiesWidget::CameraPropertiesWidget(Camera* cam, QWidget *parent) : PropertiesEditorWidget(parent)
{
    this->cam = cam;
    position = new VectorEntryWidget(cam->position);
    direction = new VectorEntryWidget(cam->direction);
    up = new VectorEntryWidget(cam->up);
    right = new VectorEntryWidget(cam->right);
    screen_dist = new FloatEdit(cam->screen_dist);
    width = new FloatEdit(cam->width);
    height = new FloatEdit(cam->height);
    layout->addRow("Position", position);
    layout->addRow("Direction", direction);
    layout->addRow("Up", up);
    layout->addRow("Right", right);
    layout->addRow("Distance to screen", screen_dist);
    layout->addRow("Width", width);
    layout->addRow("Height", height);

    connect(position, SIGNAL(modified(Vector3D)), this, SLOT(updateObject()));
    connect(direction, SIGNAL(modified(Vector3D)), this, SLOT(updateObject()));
    connect(up, SIGNAL(modified(Vector3D)), this, SLOT(updateObject()));
    connect(right, SIGNAL(modified(Vector3D)), this, SLOT(updateObject()));
    connect(screen_dist, SIGNAL(editingFinished()), this, SLOT(updateObject()));
    connect(width, SIGNAL(editingFinished()), this, SLOT(updateObject()));
    connect(height, SIGNAL(editingFinished()), this, SLOT(updateObject()));
}

void CameraPropertiesWidget::updateObject() {
    cam->position = position->toVector();
    cam->direction = direction->toVector();
    cam->up = up->toVector();
    cam->right = right->toVector();
    cam->screen_dist = screen_dist->getValue();
    cam->width = width->getValue();
    cam->height = height->getValue();
    emit objectModified();
}
