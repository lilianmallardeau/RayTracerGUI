#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include "widgets/widgets.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connection signal / slot
    connect(this, SIGNAL(sceneModified()), this, SLOT(BuildTreeViewModel()));
    connect(this, SIGNAL(sceneModified()), this, SLOT(renderPreview()));
    connect(this, SIGNAL(objectModified()), this, SLOT(renderPreview()));
    connect(ui->actionNewCube, SIGNAL(triggered()), this, SLOT(newCube()));
    connect(ui->actionNewSphere, SIGNAL(triggered()), this, SLOT(newSphere()));
    connect(ui->actionNewPlane, SIGNAL(triggered()), this, SLOT(newPlane()));
    connect(ui->actionNewQuad, SIGNAL(triggered()), this, SLOT(newQuad()));
    // Menu items
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openSavedScene()));
    connect(ui->actionSave_As, SIGNAL(triggered()), this, SLOT(saveScene()));
    connect(ui->actionQuit, SIGNAL(triggered()), QApplication::instance(), SLOT(quit()));


    QPixmap img("/home/vivien/taf/LOA/Projet/RayTracerGUI/Assets/wallpaper.jpg");
    ui->PicturePreview->setPixmap(img);

    // Scene & material views
    sceneTreeViewModel = new QStandardItemModel();
    ui->SceneList->setEditTriggers(QAbstractItemView::NoEditTriggers); // TODO remove this
    ui->SceneList->setHeaderHidden(true);
    // ui->SceneList->setRootIsDecorated(false);
    ui->SceneList->setModel(sceneTreeViewModel);

    materialViewModel = new QStringListModel(this);
    QStringList List;
    List << "Clair de Lune" << "Reverie" << "Prelude";
    materialViewModel->setStringList(List);
    ui->MaterialList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->MaterialList->setHeaderHidden(true);
    // ui->MaterialList->setRootIsDecorated(false);
    ui->MaterialList->setModel(materialViewModel);


    //ui->test = new VectorEntryWidget(this);

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

void MainWindow::BuildTreeViewModel() {
    sceneTreeViewModel->clear();
    QStandardItem *sceneItem = new QStandardItem(QIcon("medias/scene.png"), "Scene");

    // Adding camera
    QStandardItem *camera = new QStandardItem(QIcon("medias/camera.png"), "Camera");
    sceneItem->appendRow(camera);

    // Adding light
    QStandardItem *light = new QStandardItem(QIcon("medias/light.png"), "Light");
    sceneItem->appendRow(light);

    // Adding objects
    for (Object* obj : scene->objects) {
        sceneItem->appendRow(new QStandardItem(QIcon("medias/object.png"), QString::fromStdString(obj->name)));
    }
    sceneTreeViewModel->appendRow(sceneItem);
    ui->SceneList->expandAll();
}

void MainWindow::renderPreview() {
    scene->render(defaultWidth, defaultHeight, "display.png");
    ui->PicturePreview->setPixmap(QPixmap("display.png"));
}


void MainWindow::saveScene() {
    QFileDialog *dialog = new QFileDialog();
    dialog->setFileMode(QFileDialog::AnyFile);
    dialog->show();

    std::ofstream file("scene.json");
    file << std::setw(4) << scene->toJSON();
    file.close();
}

void MainWindow::openSavedScene() {
    QFileDialog *dialog = new QFileDialog();
    dialog->setFileMode(QFileDialog::ExistingFile);
    dialog->show();

    std::ifstream file("scene.json");
    json json_scene;
    file >> json_scene;
    file.close();

    scene = new Scene(json_scene);
    emit sceneModified();
}

