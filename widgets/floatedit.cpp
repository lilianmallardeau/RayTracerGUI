#include "floatedit.h"
#include <QDoubleValidator>

FloatEdit::FloatEdit(QWidget *parent) : QLineEdit(parent)
{
    QDoubleValidator *validator = new QDoubleValidator();
    setValidator(validator);
}
