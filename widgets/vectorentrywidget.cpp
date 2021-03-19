#include "vectorentrywidget.h"
#include <QDoubleValidator>
#include <QApplication>

VectorEntryWidget::VectorEntryWidget(QWidget *parent) : QWidget(parent)
{
    layout = new QHBoxLayout(this);
    x = new FloatEdit();
    y = new FloatEdit();
    z = new FloatEdit();
    x->setPlaceholderText("x");
    y->setPlaceholderText("y");
    z->setPlaceholderText("z");

    layout->addWidget(x);
    layout->addWidget(y);
    layout->addWidget(z);

    connect(x, SIGNAL(editingFinished()), this, SLOT(slotVectorModified()));
    connect(y, SIGNAL(editingFinished()), this, SLOT(slotVectorModified()));
    connect(z, SIGNAL(editingFinished()), this, SLOT(slotVectorModified()));
}

VectorEntryWidget::VectorEntryWidget(Vector3D v, QWidget *parent) : VectorEntryWidget(parent) {
    x->setText(QString::number(v.x));
    y->setText(QString::number(v.y));
    z->setText(QString::number(v.z));
};

void VectorEntryWidget::slotVectorModified() {
    emit modified(this->toVector());
}

Vector3D VectorEntryWidget::toVector() {
    return Vector3D(x->text().toFloat(), y->text().toFloat(), z->text().toFloat());
}

void VectorEntryWidget::setPlaceholders(QString x_placeholder, QString y_placeholder, QString z_placeholder) {
    x->setPlaceholderText(x_placeholder);
    y->setPlaceholderText(y_placeholder);
    z->setPlaceholderText(z_placeholder);
}