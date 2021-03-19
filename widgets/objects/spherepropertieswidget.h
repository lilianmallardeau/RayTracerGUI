#ifndef SPHEREPROPERTIESWIDGET_H
#define SPHEREPROPERTIESWIDGET_H

#include <Sphere.h>
#include "../propertieseditorwidget.h"
#include "../vectorentrywidget.h"
#include "../floatedit.h"
#include <QComboBox>

class SpherePropertiesWidget : public PropertiesEditorWidget
{
    Q_OBJECT
public:
    explicit SpherePropertiesWidget(Sphere* sphere, QWidget *parent = nullptr);
    void updateMaterials(QStandardItemModel *) override;

private:
    VectorEntryWidget *center;
    FloatEdit *radius;
    QComboBox *materials;
    Sphere* obj;

private slots:
    void updateObject();

};

#endif // SPHEREPROPERTIESWIDGET_H
