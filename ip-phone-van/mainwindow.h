#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "AudioIO.h"
#include "dialog_info.h"
#include "dialog_packetdelete.h"
#include "functions.h"

namespace Ui {

void resetPlayerButtons();

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

    void on_action_new_triggered();

    void on_action_save_triggered();

    void on_action_playpause_triggered(bool checked);

    void on_action_stop_triggered();

public:

    Ui::MainWindow *ui;

private:
    /**
     * @brief Set up axis, set up labels, user interactions, etc.
     */
    void plotSetup();

    AudioIO *file;

    void plotReplot();

    void actionsEnabled(bool state);

};


#endif // MAINWINDOW_H
