#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <list>
#include <thread>
#include <QMainWindow>
#include <QStandardItemModel>
#include <QStringListModel>
#include <QStatusBar>
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
    std::thread* currentPreviewRendering = nullptr;

    Object *lastObjectSelected = nullptr;
    Material *lastMaterialSelected = nullptr;
    enum {
        SCENE_OBJECT,
        MATERIAL,
        NONE
    } lastElementSelected = NONE;

    // RTX
    Scene* scene = nullptr;
    QList<Material*> materials = QList<Material*>();

public slots:
    void newScene();

    void newSphere();
    void newPlane();
    void newQuad();
    void newCube();
    void newMaterial();

    void BuildTreeViewModel(); // Call when object is added / removed
    void BuildMaterialViewModel();
    void renderPreview(); // Call when object transform / material is modified
    void launchThreadedRenderPreview();

    void renderScene();

    void saveScene();
    void saveSceneAs();
    void openSavedScene();

    void exportMaterials();
    void importMaterials();

    void updatePropertiesEditorWidget();
    void sceneObjectSelected(const QModelIndex &index);
    void materialSelected(const QModelIndex &index);

    void deleteSelectedElement();

signals:
    void sceneModified(); // Rebuild scene treeView and render preview
    void objectModified(); // Render preview only
    void materialModified(); // Rebuild materials list and render preview

};
#endif // MAINWINDOW_H
