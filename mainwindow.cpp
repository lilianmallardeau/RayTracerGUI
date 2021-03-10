#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap img("/home/vivien/taf/LOA/Projet/RayTracerGUI/Assets/wallpaper.jpg");
    QPixmap sImg = img.scaled(ui->PicturePreview->width(), ui->PicturePreview->height(), Qt::KeepAspectRatio);

    // qDebug() << "PicturePreview size : " << ui->PicturePreview->width() << ", " << ui->PicturePreview->height();
    // qDebug() << "Image size : " << img.width() << ", " << img.height();
    // qDebug() << "Scaled image size : " << sImg.width() << ", " << sImg.height();

    //ui->PicturePreview->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);  <- that's the right one. now done from designer tab directly.
    ui->PicturePreview->setPixmap(img);
    //ui->PicturePreview->resize(ui->PicturePreview->pixmap(Qt::ReturnByValue).size());
    //ui->PicturePreview->setScaledContents(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
