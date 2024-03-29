#define ENABLE_PARALLEL_PREVIEW_RENDERING 1

#include "mainwindow.h"
#include "ui_mainwindow.h"
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
#if ENABLE_PARALLEL_PREVIEW_RENDERING == 1
    connect(this, SIGNAL(sceneModified()), this, SLOT(launchThreadedRenderPreview()));
    connect(this, SIGNAL(objectModified()), this, SLOT(launchThreadedRenderPreview()));
#else
    connect(this, SIGNAL(sceneModified()), this, SLOT(renderPreview()));
    connect(this, SIGNAL(objectModified()), this, SLOT(renderPreview()));
#endif
    connect(this, SIGNAL(materialModified()), this, SLOT(BuildMaterialViewModel()));
    connect(this, SIGNAL(materialModified()), this, SIGNAL(objectModified()));
    connect(ui->SceneList, SIGNAL(clicked(QModelIndex)), this, SLOT(sceneObjectSelected(QModelIndex))); // Signal emitted when selecting item in tree view
    connect(ui->MaterialList, SIGNAL(clicked(QModelIndex)), this, SLOT(materialSelected(QModelIndex)));

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
    connect(ui->actionExportMaterials, SIGNAL(triggered()), this, SLOT(exportMaterials()));
    connect(ui->actionImportMaterials, SIGNAL(triggered()), this, SLOT(importMaterials()));
    connect(ui->actionDeleteItem, SIGNAL(triggered()), this, SLOT(deleteSelectedElement()));


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

    // Set splitter disposition
    QList<int> Sizes;
    Sizes.append(0.2 * height());
    Sizes.append(0.8 * height());
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
    BuildMaterialViewModel();
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
        //item->setData(QVariant::fromValue<float>(mat->alpha));
        item->setData(QVariant::fromValue<Material*>(mat));
        materialViewModel->appendRow(item);
    }
}

void MainWindow::renderPreview() {
    QString previewFilePath = QDir::tempPath() + "/raytracer_preview_display.png";
    statusBar()->showMessage("Rendering preview...");
    scene->render(defaultWidth, defaultHeight, previewFilePath.toStdString());
    ui->PicturePreview->setPixmap(QPixmap(previewFilePath));
    QFile::remove(previewFilePath);
    statusBar()->clearMessage();
}

void MainWindow::launchThreadedRenderPreview() {
    if (currentPreviewRendering != nullptr)
        currentPreviewRendering->join();
    currentPreviewRendering = new std::thread(&MainWindow::renderPreview, this);
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

void MainWindow::exportMaterials() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Export as..."), "", tr("JSON files (*.json)"));
    if (!fileName.isEmpty()) {
        QFileInfo info(fileName);
        if (info.suffix() != "json")
            fileName += ".json";
        json materials_json;
        for (Material* mat : materials) {
            materials_json.push_back(mat->toJSON());
        }
        std::ofstream file(fileName.toStdString());
        file << std::setw(4) << materials_json;
        file.close();
    }
}

void MainWindow::importMaterials() {
    QFileDialog *dialog = new QFileDialog();
    dialog->setFileMode(QFileDialog::ExistingFile);
    dialog->setNameFilter("JSON files (*.json)");
    //dialog->setOption(QFileDialog::DontConfirmOverwrite);
    dialog->show();

    if (dialog->exec()) {
        QString filename = dialog->selectedFiles().at(0);
        std::ifstream file(filename.toStdString());
        json json_materials;
        file >> json_materials;
        file.close();

        for (const json& material : json_materials) {
            materials.push_back(new Material(material));
        }
        emit BuildMaterialViewModel();
    }
}

void MainWindow::sceneObjectSelected(const QModelIndex &index) {
    QStandardItem *item = sceneTreeViewModel->itemFromIndex(index);
    QSceneObject sceneObject = item->data().value<QSceneObject>();
    PropertiesEditorWidget *newPropertiesEditor;
    switch (sceneObject.type) {
        case ObjectTyype::CAMERA:
            newPropertiesEditor = new CameraPropertiesWidget(&scene->camera, this);
            lastElementSelected = NONE;
            break;
        case ObjectTyype::LIGHT:
            newPropertiesEditor = new LightPropertiesWidget(&scene->light, this);
            lastElementSelected = NONE;
            break;
        case ObjectTyype::OBJECT:
            lastElementSelected = SCENE_OBJECT;
            lastObjectSelected = sceneObject.obj;
            switch (sceneObject.obj->type) {
                case ObjectType::SPHERE:
                    newPropertiesEditor = new SpherePropertiesWidget((Sphere*) sceneObject.obj, materialViewModel, this);
                    break;
                case ObjectType::PLANE:
                    newPropertiesEditor = new PlanePropertiesWidget((Plane*) sceneObject.obj, materialViewModel, this);
                    break;
                case ObjectType::QUAD:
                    newPropertiesEditor = new QuadPropertiesWidget((Quad*) sceneObject.obj, materialViewModel, this);
                    break;
                case ObjectType::CUBE:
                    newPropertiesEditor = new CubePropertiesWidget((Cube*) sceneObject.obj, materialViewModel, this);
                    break;
                default:
                    lastElementSelected = NONE;
            }
            connect(newPropertiesEditor, SIGNAL(objectNameChanged()), this, SLOT(BuildTreeViewModel()));
            break;
    }
    connect(newPropertiesEditor, SIGNAL(objectModified()), this, SIGNAL(objectModified()));
    if (propertiesEditor == nullptr)
        ui->EditorLayout->replaceWidget(ui->blankWidget, propertiesEditor = newPropertiesEditor);
    else {
        ui->EditorLayout->replaceWidget(propertiesEditor, newPropertiesEditor);
        delete propertiesEditor;
        propertiesEditor = newPropertiesEditor;
        ui->EditorLayout->update();
    }
}

void MainWindow::materialSelected(const QModelIndex &index) {
    QStandardItem *item = materialViewModel->itemFromIndex(index);
    Material *mat = lastMaterialSelected = item->data().value<Material*>();
    lastElementSelected = MATERIAL;
    PropertiesEditorWidget *newPropertiesEditor = new MaterialPropertiesWidget(mat, this);
    connect(newPropertiesEditor, SIGNAL(objectModified()), this, SIGNAL(materialModified()));
    if (propertiesEditor == nullptr)
        ui->EditorLayout->replaceWidget(ui->blankWidget, propertiesEditor = newPropertiesEditor);
    else {
        ui->EditorLayout->replaceWidget(propertiesEditor, newPropertiesEditor);
        delete propertiesEditor;
        propertiesEditor = newPropertiesEditor;
        ui->EditorLayout->update();
    }
}

void MainWindow::deleteSelectedElement() {
    switch (lastElementSelected) {
        case SCENE_OBJECT:
            if (lastObjectSelected != nullptr) {
                scene->objects.remove(lastObjectSelected);
                emit sceneModified();
                lastElementSelected = NONE;
            }
            break;
        case MATERIAL:
            if (lastMaterialSelected != nullptr) {
                materials.removeAll(lastMaterialSelected);
                BuildMaterialViewModel();
                lastElementSelected = NONE;
            }
            break;
    }
}
