#ifndef QUADPROPERTIESWIDGET_H
#define QUADPROPERTIESWIDGET_H

#include <Quad.h>
#include "../propertieseditorwidget.h"
#include "../vectorentrywidget.h"
#include "../floatedit.h"

class QuadPropertiesWidget : public PropertiesEditorWidget
{
    Q_OBJECT
public:
    explicit QuadPropertiesWidget(Quad* quad, QWidget *parent = nullptr);

public:
    VectorEntryWidget *origin, *width, *height;
    Quad* obj;

private slots:
    void updateObject();

};

#endif // QUADPROPERTIESWIDGET_H
