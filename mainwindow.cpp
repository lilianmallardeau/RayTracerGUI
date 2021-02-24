#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap img("/home/vivien/taf/LOA/Projet/RayTracerGUI/Assets/wallpaper.jpg");
    QPixmap sImg = img.scaled(ui->label->width(), ui->label->height(), Qt::KeepAspectRatio);

    qDebug() << "Label size : " << ui->label->width() << ", " << ui->label->height();
    qDebug() << "Image size : " << img.width() << ", " << img.height();
    qDebug() << "Scaled image size : " << sImg.width() << ", " << sImg.height();

    //ui->label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);  <- that's the right one. now done from designer tab directly.
    ui->label->setPixmap(img);
    //ui->label->resize(ui->label->pixmap(Qt::ReturnByValue).size());
    //ui->label->setScaledContents(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
