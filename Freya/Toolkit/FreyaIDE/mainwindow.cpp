#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "preferences.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowClass)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_activated()
{
    QApplication::exit();
}

void MainWindow::on_actionPreferences_activated()
{
    Preferences prefs;
    if(prefs.exec())
    {

    }
}
