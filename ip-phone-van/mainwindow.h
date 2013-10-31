#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "AudioIO.h"
#include "dialog_info.h"
#include "functions.h"

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

    void on_action_info_triggered();

    void on_action_packetDelete_triggered();

private:
    Ui::MainWindow *ui;

    /*
     * @brief Set up axis, set up labels, user interactions, etc.
     */
    void plotSetup();

    AudioIO *file;

    void plotReplot();
};

#endif // MAINWINDOW_H
