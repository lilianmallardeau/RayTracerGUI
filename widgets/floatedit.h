#ifndef FLOATEDIT_H
#define FLOATEDIT_H

#include <QWidget>
#include <QLineEdit>

class FloatEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit FloatEdit(QWidget *parent = nullptr);

signals:

};

#endif // FLOATEDIT_H
