#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->file = new AudioIO();

    ui->setupUi(this);

    this->plotReplot();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::plotSetup()
{
    ui->customPlot->xAxis->setRange(0,1);
    ui->customPlot->yAxis->setRange(0,255);
    ui->customPlot->setInteractions( QCP::iRangeDrag | QCP::iRangeZoom );
    ui->customPlot->axisRect(0)->setRangeDrag(Qt::Horizontal);
    ui->customPlot->axisRect(0)->setRangeZoom(Qt::Horizontal);
    ui->customPlot->yAxis->setTicks(false);
    ui->customPlot->yAxis->setVisible(false);
}

void MainWindow::plotReplot()
{
    int size = file->wav_header->getHeader()->WAVE_D.subChunk2Size;

    QVector<double> x(size), y(size);
    for (int i=0; i<size; i++)
    {
        x[i] = double(i)/(size-1);
        y[i] = double(file->wav_header->getData()[i]);
    }

    this->plotSetup();
    // create graph and assign data to it:
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x,y);
    // set axes ranges, so we see all data:


    ui->customPlot->replot();
}

void MainWindow::on_action_open_triggered()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(tr("WAV files (*.wav)"));
    if(dialog.exec())
    {
        file->setPath( dialog.selectedFiles().at(0).toStdString() );
    }
    this->plotReplot();
}
