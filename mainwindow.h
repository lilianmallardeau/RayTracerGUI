#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <list>
#include "src/include/utils.h"
#include "src/include/objects.h"
#include "src/include/environment.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_New_Project_triggered();

private:
    // GUI
    Ui::MainWindow *ui;

    // RTX
    Scene* scene = nullptr;

    /** Materials */
    std::list<Material> materials;

};
#endif // MAINWINDOW_H
