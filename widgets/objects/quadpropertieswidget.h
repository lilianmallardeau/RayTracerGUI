#ifndef QUADPROPERTIESWIDGET_H
#define QUADPROPERTIESWIDGET_H

#include "../propertieseditorwidget.h"
#include "../vectorentrywidget.h"
#include "../floatedit.h"

class QuadPropertiesWidget : public PropertiesEditorWidget
{
    Q_OBJECT
public:
    explicit QuadPropertiesWidget(QWidget *parent = nullptr);

public:
    VectorEntryWidget origin, width, height;

signals:

};

#endif // QUADPROPERTIESWIDGET_H
