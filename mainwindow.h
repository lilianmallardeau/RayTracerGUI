#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <list>
#include <thread>
#include <QMainWindow>
#include <QStandardItemModel>
#include <QStringListModel>
#include "src/include/utils.h"
#include "src/include/objects.h"
#include "src/include/environment.h"
#include "widgets/widgets.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    // GUI
    Ui::MainWindow *ui;
    PropertiesEditorWidget *propertiesEditor = nullptr;
    QStandardItemModel* sceneTreeViewModel;
    QStandardItemModel* materialViewModel;
    int defaultWidth = 720, defaultHeight = 480;
    QString currentFileName = nullptr;
    std::thread* currentPreviewRendering;

    // RTX
    Scene* scene = nullptr;

    /** Materials */
    std::list<Material> materials;

public slots:
    void newScene();

    void newSphere();
    void newPlane();
    void newQuad();
    void newCube();

    void BuildTreeViewModel(); // Call when object is added / removed
    void renderPreview(); // Call when object transform / material is modified
    void launchThreadedRenderPreview();

    void renderScene();

    void saveScene();
    void saveSceneAs();
    void openSavedScene();

    void updatePropertiesEditorWidget();
    void sceneObjectSelected(const QModelIndex &index);
    void testListView(const QModelIndex &index);

signals:
    void sceneModified();
    void objectModified();

};
#endif // MAINWINDOW_H
