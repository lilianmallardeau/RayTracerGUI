#include "floatedit.h"
//#include <limits>

FloatEdit::FloatEdit(QWidget *parent) : QDoubleSpinBox(parent)
{
    //setRange(std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
    setRange(INT_MIN, INT_MAX);
}

FloatEdit::FloatEdit(float value, QWidget *parent) : FloatEdit(parent) {
    setValue(value);
}

float FloatEdit::getValue() {

    return (float) value();
}
