#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <widgets/vectorentrywidget.h>
#include <QStringListModel>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap img("/home/vivien/taf/LOA/Projet/RayTracerGUI/Assets/wallpaper.jpg");
    ui->PicturePreview->setPixmap(img);

    model1 = new QStandardItemModel();

    QStandardItem* item0 = new QStandardItem(QIcon("test.png"), "1 first item");
    QStandardItem* item1 = new QStandardItem(QIcon("test.png"), "2 second item");
    QStandardItem* item3 = new QStandardItem(QIcon("test.png"), "3 third item");
    QStandardItem* item4 = new QStandardItem("4 forth item");

    model1->appendRow(item0);
    item0->appendRow(item3);
    item0->appendRow(item4);
    model1->appendRow(item1);

    ui->SceneList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->SceneList->setModel(model1);
    ui->SceneList->setHeaderHidden(true);
    ui->SceneList->expandAll();
    //ui->SceneList->setRootIsDecorated(false);

    QStringListModel* model2;

    // Create model
    model2 = new QStringListModel(this);

    // Make data
    QStringList List;
    List << "Clair de Lune" << "Reverie" << "Prelude";

    // Populate our model
    model2->setStringList(List);

    // Glue model and view together
    ui->MaterialList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->MaterialList->setModel(model2);


    //ui->test = new VectorEntryWidget(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_New_Project_triggered()
{
    scene = new Scene(Camera(Point3D(0, 0, 10), Point3D(0, 0, -1), Vector3D(0, 1, 0), Vector3D(1, 0, 0)), Light(Point3D(0, 10, 0)));
    scene->render(1920, 1080, "scene.png");
    QPixmap img("scene.png");
    ui->PicturePreview->setPixmap(img);
}

void MainWindow::on_actionNewSphere_triggered()
{
    if (scene) {
        scene->addObject(new Sphere(Point3D(0, 0, 0), 5));
        QStandardItem *newItem = new QStandardItem("Sphere");
        model1->appendRow(newItem);
        scene->render(1920, 1080, "scene.png");
        QPixmap img("scene.png");
        ui->PicturePreview->setPixmap(img);
    }
}



void MainWindow::newSphere() {
    Sphere* sphere = new Sphere(0, 1);
    sphere->name = "New sphere";
    scene->addObject(sphere);
}

void MainWindow::newPlane() {
    Plane* plane = new Plane(0, Vector3D::k);
    plane->name = "New plane";
    scene->addObject(plane);
}

void MainWindow::newQuad() {
    Quad* quad = new Quad(0, Vector3D::i, Vector3D::j);
    quad->name = "New quad";
    scene->addObject(quad);
}

void MainWindow::newCube() {
    Cube* cube = new Cube(0, Vector3D::i, Vector3D::j, Vector3D::k);
    cube->name = "New cube";
    scene->addObject(cube);
}

void MainWindow::BuildTreeViewModel() {
    free(sceneTreeViewModel);
    sceneTreeViewModel = new QStandardItemModel();
    QStandardItem sceneItem(QIcon("medias/scene.png"), "Scene");

    // Adding camera
    QStandardItem camera(QIcon("medias/camera.png"), "Camera");
    sceneItem.appendRow(&camera);

    // Adding light
    QStandardItem light(QIcon("medias/light.png"), "Light");
    sceneItem.appendRow(&light);

    // Adding objects
    for (Object* obj : scene->objects) {
        sceneItem.appendRow(new QStandardItem(QIcon("medias/object.png"), QString::fromStdString(obj->name)));
    }
    sceneTreeViewModel->appendRow(&sceneItem);
    ui->SceneList->setModel(sceneTreeViewModel);
}




