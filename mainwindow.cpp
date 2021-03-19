#include "mainwindow.h"
#include "../build-RayTracerGUI-Desktop_Qt_5_15_2_GCC_64bit-Debug/lanceur-de-rayons_autogen/include/ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <nlohmann/json.hpp>
#include "qtCustomType/qsceneobject.h"
using json = nlohmann::json;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*********************** Connection signal / slot ***********************/
    // Updating GUI
    connect(this, SIGNAL(sceneModified()), this, SLOT(BuildTreeViewModel()));
    connect(this, SIGNAL(sceneModified()), this, SLOT(renderPreview()));
    connect(this, SIGNAL(objectModified()), this, SLOT(renderPreview()));
    connect(this, SIGNAL(materialModified()), this, SLOT(BuildMaterialViewModel()));
    connect(ui->SceneList, SIGNAL(clicked(QModelIndex)), this, SLOT(test(QModelIndex))); // Signal emited when selecting item in tree view
    connect(ui->MaterialList, SIGNAL(clicked(QModelIndex)), this, SLOT(testListView(QModelIndex)));

    // New object actions
    connect(ui->actionNewScene, SIGNAL(triggered()), this, SLOT(newScene()));
    connect(ui->actionNewCube, SIGNAL(triggered()), this, SLOT(newCube()));
    connect(ui->actionNewSphere, SIGNAL(triggered()), this, SLOT(newSphere()));
    connect(ui->actionNewPlane, SIGNAL(triggered()), this, SLOT(newPlane()));
    connect(ui->actionNewQuad, SIGNAL(triggered()), this, SLOT(newQuad()));
    connect(ui->actionNew_Material, SIGNAL(triggered()), this, SLOT(newMaterial()));

    // Menu items
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openSavedScene()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveScene()));
    connect(ui->actionSave_As, SIGNAL(triggered()), this, SLOT(saveSceneAs()));
    connect(ui->actionQuit, SIGNAL(triggered()), QApplication::instance(), SLOT(quit()));
    connect(ui->actionRender, SIGNAL(triggered()), this, SLOT(renderScene()));


    /*********************** Scene & material views ***********************/
    sceneTreeViewModel = new QStandardItemModel();
    ui->SceneList->setEditTriggers(QAbstractItemView::NoEditTriggers); // TODO remove this
    ui->SceneList->setHeaderHidden(true);
    ui->SceneList->setModel(sceneTreeViewModel);
    // Actually so sad, drag & drop = much work. Moved to wishlist
//    ui->SceneList->setDragEnabled(true);
//    ui->SceneList->viewport()->setAcceptDrops(true);
//    ui->SceneList->setDropIndicatorShown(true);


    materialViewModel = new QStandardItemModel();
    ui->MaterialList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->MaterialList->setHeaderHidden(true);
    ui->MaterialList->setModel(materialViewModel);
    QStandardItem *item = new QStandardItem("chose");
    Material mat(Color(36));
    mat.name = "chose";
    item->setData(QVariant::fromValue<Material>(mat));
    materials.append(&mat);
    materialViewModel->appendRow(item);

    // Set splitter disposition
    QList<int> Sizes;
    Sizes.append(0.15 * height());
    Sizes.append(0.85 * height());
    ui->splitter->setSizes(Sizes);

    this->showMaximized();
    newScene();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newScene() {
    scene = new Scene(Camera(Point3D(0, 0, 10), Point3D(0, 0, -1), Vector3D(0, 1, 0), Vector3D(1, 0, 0)), Light(Point3D(0, 10, 0)));
    emit sceneModified();
}

void MainWindow::newSphere() {
    Sphere* sphere = new Sphere(0, 1);
    sphere->name = "New sphere";
    scene->addObject(sphere);
    emit sceneModified();
}

void MainWindow::newPlane() {
    Plane* plane = new Plane(0, Vector3D::k);
    plane->name = "New plane";
    scene->addObject(plane);
    emit sceneModified();
}

void MainWindow::newQuad() {
    Quad* quad = new Quad(0, Vector3D::i, Vector3D::j);
    quad->name = "New quad";
    scene->addObject(quad);
    emit sceneModified();
}

void MainWindow::newCube() {
    Cube* cube = new Cube(0, Vector3D::i, Vector3D::j, Vector3D::k);
    cube->name = "New cube";
    scene->addObject(cube);
    emit sceneModified();
}

void MainWindow::newMaterial() {
    Material* mat = new Material();
    mat->name = "New Material";
    materials.append(mat);
    qDebug() << materials;
    emit materialIsModified();
    emit sceneModified(); // TODO emit only if material is assigned in scene
}

void MainWindow::BuildTreeViewModel() {
    sceneTreeViewModel->clear();
    QStandardItem *sceneItem = new QStandardItem(QIcon("medias/scene.png"), "Scene");

    // Adding camera
    QStandardItem *camera = new QStandardItem(QIcon("medias/camera.png"), "Camera");
    camera->setData(QVariant::fromValue<QSceneObject>(QSceneObject(ObjectTyype::CAMERA)));
    sceneItem->appendRow(camera);

    // Adding light
    QStandardItem *light = new QStandardItem("Light");
    light->setData(QVariant::fromValue<QSceneObject>(QSceneObject(ObjectTyype::LIGHT)));
    light->setIcon(QIcon("Asset/light.png"));
    sceneItem->appendRow(light);

    // Adding objects
    for (Object* obj : scene->objects) {
        QStandardItem *item = new QStandardItem(QIcon("medias/object.png"), QString::fromStdString(obj->name));
        item->setData(QVariant::fromValue<QSceneObject>(QSceneObject(obj)));
        sceneItem->appendRow(item);
        //sceneItem->appendRow(new QStandardItem(QIcon("medias/object.png"), QString::fromStdString(obj->name)));
    }
    sceneTreeViewModel->appendRow(sceneItem);
    ui->SceneList->expandAll();
}

void MainWindow::BuildMaterialViewModel() {
    materialViewModel->clear();
    for (Material *mat : materials) {
        QStandardItem *item = new QStandardItem(QString::fromStdString(mat->name));
        item->setData(QVariant::fromValue<Material>(*mat));
        materialViewModel->appendRow(item);
    }
}

void MainWindow::renderPreview() {
    scene->render(defaultWidth, defaultHeight, "display.png");
    ui->PicturePreview->setPixmap(QPixmap("display.png"));
}

void MainWindow::renderScene() {
    QString pictureName = QFileDialog::getSaveFileName(this, tr("Render scene..."), "", tr("PNG files (*.png)"));
    if (!pictureName.isEmpty()) {
        QFileInfo info(pictureName);
        if (info.suffix() != "png")
            pictureName += ".png";
        scene->render(1920, 1080, pictureName.toStdString());
    }
}

void MainWindow::saveScene() {
    if (currentFileName != nullptr) {
        std::ofstream file(currentFileName.toStdString());
        file << std::setw(4) << scene->toJSON();
        file.close();
    }
    else
        saveSceneAs();
}

void MainWindow::saveSceneAs() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save as..."), "", tr("JSON files (*.json)"));
    if (!fileName.isEmpty()) {
        QFileInfo info(fileName);
        if (info.suffix() != "json")
            fileName += ".json";
        std::ofstream file(fileName.toStdString());
        file << std::setw(4) << scene->toJSON();
        file.close();
        if (currentFileName == nullptr) {
            currentFileName = fileName;
            this->setWindowTitle(QString(currentFileName));
        }
    }

//    Deprecated because nul

//    QFileDialog *dialog = new QFileDialog();
//    dialog->setFileMode(QFileDialog::AnyFile);
//    dialog->show();

//    if (dialog->exec()) {
//        QString filename = dialog->selectedFiles().at(0);
//        std::ofstream file(filename.toStdString());
//        file << std::setw(4) << scene->toJSON();
//        file.close();
//    }
}

void MainWindow::openSavedScene() {
    QFileDialog *dialog = new QFileDialog();
    dialog->setFileMode(QFileDialog::ExistingFile);
    dialog->setNameFilter("JSON files (*.json)");
    //dialog->setOption(QFileDialog::DontConfirmOverwrite);
    dialog->show();

    if (dialog->exec()) {
        QString filename = dialog->selectedFiles().at(0);
        std::ifstream file(filename.toStdString());
        json json_scene;
        file >> json_scene;
        file.close();
        currentFileName = filename;

        scene = new Scene(json_scene);
        emit sceneModified();
    }
}

void MainWindow::updatePropertiesEditorWidget() {

}

void MainWindow::test(const QModelIndex &index) {
    QStandardItem *item = sceneTreeViewModel->itemFromIndex(index);
    qDebug() << item->data().value<QSceneObject>();
    //qDebug() << item;
    //CameraPropertiesWidget *popUp = new CameraPropertiesWidget(); // SAMARCHEPAS
    //popUp->show();
}

void MainWindow::testListView(const QModelIndex &index) {
    QStandardItem *item = materialViewModel->itemFromIndex(index);
    qDebug() << QString::fromStdString(item->data().value<Material>().name);
}
