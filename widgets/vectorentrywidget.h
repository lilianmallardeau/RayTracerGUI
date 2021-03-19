#ifndef VECTORENTRYWIDGET_H
#define VECTORENTRYWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QHBoxLayout>
#include "floatedit.h"
#include "../src/utils/Vector3D.h"

class VectorEntryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VectorEntryWidget(QWidget *parent = nullptr);
    explicit VectorEntryWidget(Vector3D v, QWidget *parent = nullptr);

    Vector3D toVector();

    void setPlaceholders(QString x, QString y, QString z);

private:
    FloatEdit *x, *y, *z;
    QHBoxLayout *layout;

signals:
    void modified(Vector3D);

private slots:
    void slotVectorModified();
};

#endif // VECTORENTRYWIDGET_H
