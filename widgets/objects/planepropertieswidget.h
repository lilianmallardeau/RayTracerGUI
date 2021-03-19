#ifndef PLANEPROPERTIESWIDGET_H
#define PLANEPROPERTIESWIDGET_H

#include <Plane.h>
#include "../propertieseditorwidget.h"
#include "../vectorentrywidget.h"
#include "../floatedit.h"
#include <QComboBox>

class PlanePropertiesWidget : public PropertiesEditorWidget
{
    Q_OBJECT
public:
    explicit PlanePropertiesWidget(Plane* plane, QWidget *parent = nullptr);
    void updateMaterials(QStandardItemModel *) override;

private:
    VectorEntryWidget *point, *normal;
    QComboBox *materials;
    Plane* obj;

private slots:
    void updateObject();

};

#endif // PLANEPROPERTIESWIDGET_H
