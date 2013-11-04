#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->file = new AudioIO();
    ui->setupUi(this);
    this->plotSetup();
    this->actionsEnabled(false);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::plotSetup()
{
    std::map <std::string, std::string> wav = file->wav_header->getHeader();
    int bps = wav.empty()?0:str2int(wav["bitsPerSample"]);
    double time = 1.* str2int(wav["subChunk2Size"]) / bps;

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
    std::map <std::string, std::string> wav = file->wav_header->getHeader();
    int bps = wav.empty()?0: str2int(wav["bitsPerSample"]);
    int size = wav.empty()?0: str2int(wav["subChunk2Size"]);
    double time = double(size) / bps;

    const unsigned char * data = file->wav_header->data;

    QVector<double> x(size), y(size);
    for (int i=0; i<size; i++)
    {
        x[i] = time*(double(i)/(size-1)); 
        y[i] = double(data[i]);
    }

    this->plotSetup();
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x,y);
    ui->customPlot->replot();
}

void MainWindow::actionsEnabled(bool state)
{
    // Disabled
    ui->action_save->setDisabled(!state);
    ui->action_saveas->setDisabled(!state);
    ui->action_info->setDisabled(!state);
    ui->action_packetDelete->setDisabled(!state);
    ui->action_packetRecover->setDisabled(!state);
    ui->action_stop->setDisabled(!state);
    // Visible
    ui->action_playpause->setVisible(state);
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
        QString path = dialog.selectedFiles().at(0);
        file->setPath( path.toStdString() );
        this->plotReplot();
        setWindowTitle("Waver (" + path + ")");
        this->actionsEnabled(true);
    }
}

void MainWindow::on_action_exit_triggered()
{
    exit(0);
}

void MainWindow::on_action_info_triggered()
{
    std::map<std::string,std::string> wav = file->wav_header->getHeader();

    if(wav.empty())
        return;

    Dialog_Info *di = new Dialog_Info(wav, this);
    if(di->exec())
    {
        delete di;
    }
}

void MainWindow::on_action_packetDelete_triggered()
{
    std::map<std::string,std::string> wav = file->wav_header->getHeader();

    if(wav.empty())
        return;

    Dialog_PacketDelete *dpd = new Dialog_PacketDelete(this);

    double loss_rate = 0;
    int    packet_length = 1;

    if(dpd->exec())
    {
        loss_rate     = dpd->loss_rate;
        packet_length = dpd->packet_length;
        // true => pressed ok
        if(dpd->accepted)
        {
            /* TODO:
            int packets_to_loss = str2int(wav["subChunk2Size"]) * loss_rate;
            for(int i=0; i<packets_to_loss; i++)
            {
                file->wav_header->data[rand()%]
            }
            */
        }

        delete dpd;
    }
}


void MainWindow::on_action_new_triggered()
{
    delete file->wav_header;
    file->wav_header = new WAV();
    setWindowTitle("Waver");
    this->actionsEnabled(false);
    this->plotReplot();

}


void MainWindow::on_action_save_triggered()
{

}


void MainWindow::on_action_playpause_triggered(bool checked)
{
    if(checked)
    {
        file->startPlayback();
        ui->action_playpause->setIcon(QIcon(":/recources/buttons/buttonPause.png"));
    }
    else
    {
        if(file->isOpen())
            file->pausePlayback();
        ui->action_playpause->setIcon(QIcon(":/recources/buttons/buttonPlay.png"));
    }
}


void MainWindow::on_action_stop_triggered()
{
    ui->action_playpause->setChecked(false);
    if(file->isOpen())
    {
        file->stopPlayback();
    }
}
