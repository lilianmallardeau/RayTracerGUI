#ifndef PROPERTIESEDITORWIDGET_H
#define PROPERTIESEDITORWIDGET_H

#include <QWidget>
#include <QFormLayout>

class PropertiesEditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PropertiesEditorWidget(QWidget *parent = nullptr);

protected:
    QFormLayout *layout;

signals:

};

#endif // PROPERTIESEDITORWIDGET_H
