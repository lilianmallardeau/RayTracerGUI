#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <list>
#include <QStandardItemModel>
#include "src/include/utils.h"
#include "src/include/objects.h"
#include "src/include/environment.h"
#include <QStringListModel>

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
    //QStandardItemModel* model1;
    QStandardItemModel* sceneTreeViewModel;
    QStringListModel* materialViewModel;
    int defaultWidth = 720, defaultHeight = 480;
    QString currentFileName = nullptr;

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
    void renderScene();

    void saveScene();
    void saveSceneAs();
    void openSavedScene();

signals:
    void sceneModified();
    void objectModified();

};
#endif // MAINWINDOW_H
