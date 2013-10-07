#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "AudioIO.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_action_open_triggered();

    void on_action_exit_triggered();

private:
    Ui::MainWindow *ui;

    void plotSetup();

    AudioIO *file;

    void plotReplot();
};

#endif // MAINWINDOW_H
