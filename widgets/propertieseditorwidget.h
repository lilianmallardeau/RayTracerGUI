#ifndef PROPERTIESEDITORWIDGET_H
#define PROPERTIESEDITORWIDGET_H

#include <QWidget>
#include <QFormLayout>
#include <QStandardItemModel>

class PropertiesEditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PropertiesEditorWidget(QWidget *parent = nullptr, QStandardItemModel *materialModel = nullptr);

protected:
    QFormLayout *layout;
    QStandardItemModel *materialModel;

signals:
    void objectModified();
};

#endif // PROPERTIESEDITORWIDGET_H
