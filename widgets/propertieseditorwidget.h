#ifndef PROPERTIESEDITORWIDGET_H
#define PROPERTIESEDITORWIDGET_H

#include <QWidget>
#include <QFormLayout>
#include <QStandardItemModel>

class PropertiesEditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PropertiesEditorWidget(QWidget *parent = nullptr);
    virtual void updateMaterials(QStandardItemModel *) = 0;

protected:
    QFormLayout *layout;

signals:
    void objectModified();
};

#endif // PROPERTIESEDITORWIDGET_H
