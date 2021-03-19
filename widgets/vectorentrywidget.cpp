#include "vectorentrywidget.h"
#include <QDoubleValidator>
#include <QApplication>

VectorEntryWidget::VectorEntryWidget(QWidget *parent) : QWidget(parent)
{
    layout = new QHBoxLayout(this);
    x = new FloatEdit();
    y = new FloatEdit();
    z = new FloatEdit();

    layout->addWidget(x);
    layout->addWidget(y);
    layout->addWidget(z);

    connect(x, SIGNAL(valueChanged(double)), this, SLOT(slotVectorModified()));
    connect(y, SIGNAL(valueChanged(double)), this, SLOT(slotVectorModified()));
    connect(z, SIGNAL(valueChanged(double)), this, SLOT(slotVectorModified()));
}

VectorEntryWidget::VectorEntryWidget(Vector3D v, QWidget *parent) : VectorEntryWidget(parent) {
    x->setValue(v.x);
    y->setValue(v.y);
    z->setValue(v.z);
};

void VectorEntryWidget::slotVectorModified() {
    emit modified(this->toVector());
}

Vector3D VectorEntryWidget::toVector() {
    return Vector3D(x->getValue(), y->getValue(), z->getValue());
}
