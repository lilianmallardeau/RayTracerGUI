#ifndef FLOATEDIT_H
#define FLOATEDIT_H

#include <QWidget>
#include <QDoubleSpinBox>

class FloatEdit : public QDoubleSpinBox
{
    Q_OBJECT
public:
    explicit FloatEdit(QWidget *parent = nullptr);
    explicit FloatEdit(float value, QWidget *parent = nullptr);

    float getValue();

signals:

};

#endif // FLOATEDIT_H
