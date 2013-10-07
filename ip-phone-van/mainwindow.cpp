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
    int bps = file->wav_header->getHeader()->WAVE_F.bitsPerSample;
    double time = 1.* file->wav_header->getHeader()->WAVE_D.subChunk2Size / bps;

    ui->customPlot->yAxis->setRange(-1,256);
    // Set ranges to top and bottom axis
    ui->customPlot->xAxis->setRangeLower(0);
    ui->customPlot->xAxis->setRangeUpper(time);
    ui->customPlot->setInteractions( QCP::iRangeDrag | QCP::iRangeZoom );
    ui->customPlot->axisRect(0)->setRangeDrag(Qt::Horizontal);
    ui->customPlot->axisRect(0)->setRangeZoom(Qt::Horizontal);
    ui->customPlot->yAxis->setVisible(false);
    ui->customPlot->xAxis->setLabel("Time, ms");
}

void MainWindow::plotReplot()
{
    int bps = file->wav_header->getHeader()->WAVE_F.bitsPerSample;
    int size = file->wav_header->getHeader()->WAVE_D.subChunk2Size;
    double time = double(size) / bps;
    QVector<double> x(size), y(size);
    for (int i=0; i<size; i++)
    {
        x[i] = time*(double(i)/(size-1));
        y[i] = double(file->wav_header->data[i]);
    }

    this->plotSetup();
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x,y);
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

void MainWindow::on_action_exit_triggered()
{
    exit(0);
}
