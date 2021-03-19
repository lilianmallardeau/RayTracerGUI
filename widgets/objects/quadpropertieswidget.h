#ifndef QUADPROPERTIESWIDGET_H
#define QUADPROPERTIESWIDGET_H

#include <Quad.h>
#include "ObjectPropertiesWidget.h"
#include "../vectorentrywidget.h"
#include "../floatedit.h"

class QuadPropertiesWidget : public ObjectPropertiesWidget
{
    Q_OBJECT
public:
    explicit QuadPropertiesWidget(Quad* quad, QStandardItemModel *materialModel, QWidget *parent = nullptr);

public:
    VectorEntryWidget *origin, *width, *height;
    Quad* quad;

private slots:
    void updateObject() override;

};

#endif // QUADPROPERTIESWIDGET_H
