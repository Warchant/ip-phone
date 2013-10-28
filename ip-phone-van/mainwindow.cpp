#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->dui  = new dialog_packets(this,nullptr);
    this->file = new AudioIO();
    ui->setupUi(this);
    this->plotSetup();
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
    // only existing file can be selected
    dialog.setFileMode(QFileDialog::ExistingFile);
    // wav files only
    dialog.setNameFilter(tr("WAV files (*.wav)"));
    // exec dialog
    if(dialog.exec())
    {
        file->setPath( dialog.selectedFiles().at(0).toStdString() );
        this->plotReplot();
    }
}

void MainWindow::on_action_exit_triggered()
{
    exit(0);
}

void MainWindow::on_action_info_triggered()
{
    // Fill form rows
    tableViewRow *rows = new tableViewRow[13]; // 13 is the number of chunks in WAV header
    // RIFF section
    rows[0].setEditable(false).setKey("chunkID").setValues(new std::string(file->wav_header->getHeader()->RIFF.chunkID));
    rows[1].setEditable(false).setKey("chunkSize").setValues(new std::string(file->wav_header->getHeader()->RIFF.chunkSize));
    rows[2].setEditable(false).setKey("format").setValues(new std::string(file->wav_header->getHeader()->RIFF.format));
    // WAVE_D section
    rows[3].setEditable(false).setKey("subChunk2Size").setValues(new std::string(file->wav_header->getHeader()->WAVE_D.subChunk2Size));
    rows[4].setEditable(false).setKey("subChunkID").setValues(new std::string(file->wav_header->getHeader()->WAVE_D.subChunkID));
    // WAVE_F section
    rows[5].setEditable(false).setKey("audioFormat").setValues(new std::string(file->wav_header->getHeader()->WAVE_F.audioFormat));
    rows[6].setEditable(false).setKey("bitsPerSample").setValues(new std::string(file->wav_header->getHeader()->WAVE_F.bitsPerSample));
    rows[7].setEditable(false).setKey("blockAlign").setValues(new std::string(file->wav_header->getHeader()->WAVE_F.blockAlign));
    rows[8].setEditable(false).setKey("byteRate").setValues(new std::string(file->wav_header->getHeader()->WAVE_F.byteRate));
    rows[9].setEditable(false).setKey("numChannels").setValues(new std::string(file->wav_header->getHeader()->WAVE_F.numChannels));
    rows[10].setEditable(false).setKey("sampleRate").setValues(new std::string(file->wav_header->getHeader()->WAVE_F.sampleRate));
    rows[11].setEditable(false).setKey("subChunkID").setValues(new std::string(file->wav_header->getHeader()->WAVE_F.subChunkID));
    rows[12].setEditable(false).setKey("subChunkSize").setValues(new std::string(file->wav_header->getHeader()->WAVE_F.subChunkSize));
    // Show form
    delete this->dui;
    this->dui = new dialog_packets(this, rows);
    this->dui->show();

}
