#ifndef FLOATEDIT_H
#define FLOATEDIT_H

#include <QWidget>
#include <QLineEdit>

class FloatEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit FloatEdit(QWidget *parent = nullptr);
    explicit FloatEdit(float value, QWidget *parent = nullptr);

    float getValue();

signals:

};

#endif // FLOATEDIT_H
