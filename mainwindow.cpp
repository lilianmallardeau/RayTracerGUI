#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap img("/home/vivien/taf/LOA/Projet/RayTracerGUI/Assets/wallpaper.jpg");

    // Essais pour resize l'image à la bonne taille
    //QPixmap sImg = img.scaled(ui->PicturePreview->width(), ui->PicturePreview->height(), Qt::KeepAspectRatio);
    // qDebug() << "PicturePreview size : " << ui->PicturePreview->width() << ", " << ui->PicturePreview->height();
    // qDebug() << "Image size : " << img.width() << ", " << img.height();
    // qDebug() << "Scaled image size : " << sImg.width() << ", " << sImg.height();

    //ui->PicturePreview->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);  <- that's the right one. now done from designer tab directly.
    //ui->PicturePreview->resize(ui->PicturePreview->pixmap(Qt::ReturnByValue).size());
    //ui->PicturePreview->setScaledContents(true);

    ui->PicturePreview->setPixmap(img);
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
