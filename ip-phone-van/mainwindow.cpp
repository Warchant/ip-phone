#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->wav = new WAV();

    ui->setupUi(this);
    int bps  = wav->getHeader()->WAVE_F.bitsPerSample;
    int size = wav->getHeader()->WAVE_D.subChunk2Size;

    QVector<double> x(size), y(size);
    for (int i=0; i<size; i++)
    {
        x[i] = double(i)/(size-1);
        y[i] = double(wav->getData()[i]);
    }

    this->setupPlot();
    // create graph and assign data to it:
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x,y);
    // set axes ranges, so we see all data:


    ui->customPlot->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupPlot()
{
    ui->customPlot->xAxis->setRange(0,1);
    ui->customPlot->yAxis->setRange(0,255);
    ui->customPlot->setInteractions( QCP::iRangeDrag | QCP::iRangeZoom );
    ui->customPlot->axisRect(0)->setRangeDrag(Qt::Horizontal);
    ui->customPlot->axisRect(0)->setRangeZoom(Qt::Horizontal);
    ui->customPlot->yAxis->setTicks(false);
    ui->customPlot->yAxis->setVisible(false);
}

void MainWindow::on_action_open_triggered()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(tr("WAV files (*.wav)"));
    if(dialog.exec())
    {
        a.setPath( dialog.selectedFiles().at(0).toStdString() );
    }
}
