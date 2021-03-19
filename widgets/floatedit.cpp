#include "floatedit.h"
#include <QDoubleValidator>

FloatEdit::FloatEdit(QWidget *parent) : QLineEdit(parent)
{
    QDoubleValidator *validator = new QDoubleValidator();
    setValidator(validator);
}

FloatEdit::FloatEdit(float value, QWidget *parent) : FloatEdit(parent) {
    setText(QString::number(value));
}

float FloatEdit::getValue() {
    return text().toFloat();
}
