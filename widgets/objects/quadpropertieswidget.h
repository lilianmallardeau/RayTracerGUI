#ifndef QUADPROPERTIESWIDGET_H
#define QUADPROPERTIESWIDGET_H

#include <Quad.h>
#include "../propertieseditorwidget.h"
#include "../vectorentrywidget.h"
#include "../floatedit.h"
#include <QComboBox>

class QuadPropertiesWidget : public PropertiesEditorWidget
{
    Q_OBJECT
public:
    explicit QuadPropertiesWidget(Quad* quad, QWidget *parent = nullptr);
    void updateMaterials(QStandardItemModel *) override;

public:
    VectorEntryWidget *origin, *width, *height;
    QComboBox *materials;
    Quad* obj;

private slots:
    void updateObject();

};

#endif // QUADPROPERTIESWIDGET_H
