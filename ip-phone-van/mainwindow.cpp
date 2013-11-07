#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->file = new AudioIO();
    ui->setupUi(this);
    //this->plotSetup();
    this->actionsEnabled(false);
    ui->customPlot->xAxis->setVisible(false);
    ui->customPlot->yAxis->setVisible(false);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::plotSetup()
{
    std::map <std::string, std::string> wav = file->wav_header->getHeader();
    int     bps = wav.empty()?0:str2int(wav["bitsPerSample"]);
    int    size = str2int(wav["subChunk2Size"]);
    double time = 1.* size / bps;
    int     min = 255;
    int     max = 0;

    for(int i=0; i<size; i++)
    {
        min = min > file->wav_header->data[i] ? file->wav_header->data[i] : min;
        max = max < file->wav_header->data[i] ? file->wav_header->data[i] : max;
    }

    // Set ranges to top and bottom axis
    ui->customPlot->yAxis->setRange(min-1,max+1);
    ui->customPlot->xAxis->setRange(0, time);
    ui->customPlot->setInteractions( QCP::iRangeDrag | QCP::iRangeZoom );
    ui->customPlot->axisRect(0)->setRangeDrag(Qt::Horizontal);
    ui->customPlot->axisRect(0)->setRangeZoom(Qt::Horizontal);
    ui->customPlot->xAxis->setLabel("Time, ms");
    ui->customPlot->yAxis->setLabel("Amplitude");
    ui->customPlot->setNoAntialiasingOnDrag(true);
    ui->customPlot->xAxis->setVisible(true);
    ui->customPlot->yAxis->setVisible(true);
}

void MainWindow::plotReplot()
{
    std::vector <int> empty;
    this->plotReplot(empty);
}


void MainWindow::plotReplot(std::vector <int> ignore)
{
    std::map <std::string, std::string> wav = file->wav_header->getHeader();
    int     bps = wav.empty()?0: str2int(wav["bitsPerSample"]);
    int    size = wav.empty()?0: str2int(wav["subChunk2Size"]);
    double time = double(size) / bps;

    const unsigned char * data = file->wav_header->data;

    QVector<double> x(size), y(size);
    for (int i=0; i<size; i++)
    {
        x[i] = time*(double(i)/(size-1)); 
        y[i] = double(data[i]);
    }
    if(!ignore.empty())
    {
        int mean = std::accumulate(y.begin(), y.end(), 0.0) / y.size();
        for (int i=0; i<ignore.size();i++ )
        {
            for(int j=0; j<this->packetLength; j++)
            {
                y[ignore[i]*this->packetLength + j] = mean ;
            }
        }
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
    ui->action_playpause->setDisabled(!state);
}


std::vector <int> MainWindow::randVector(int begin, int end, int amount)
{
    int length = end - begin;
    std::vector <int> rnd(length);
    for(int i=0; i<length; i++)
    {
        rnd[i] = (i+begin);
    }
    std::random_shuffle(rnd.begin(), rnd.end());
    rnd.resize(amount);
    return rnd;
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

    int length = str2int(wav["subChunk2Size"]);

    Dialog_PacketDelete *dpd = new Dialog_PacketDelete(length,this);

    int to_delete     = 0;
    int packet_length = 1;

    if(dpd->exec()) //show dialog
    {
        to_delete     = dpd->to_delete;         // amount of packets to delete
        packet_length = dpd->packet_length;     // packet size in bytes
        this->packetLength = packet_length;
        int size      = length/packet_length;   // size of new array: data divided into packets

        std::vector <int> del_index = randVector(0,size,to_delete);
        std::for_each(del_index.begin(), del_index.end(),[&](int &a){
            printf("%i\t ",a);
        });
        if(!del_index.empty())
        {
            const QCPDataMap *dataMap = ui->customPlot->graph(0)->data();
            QVector <double> y;
            for(QMap<double, QCPData>::const_iterator it = dataMap->constBegin();
                it!=dataMap->constEnd(); ++it)
            {
                y.push_back(it.value().value);
            }
            file->wav_header->convert2data(y);
        }
        this->plotReplot(del_index);
    }
    delete dpd;


}


void MainWindow::on_action_new_triggered()
{
    delete file->wav_header;
    file->wav_header = new WAV();
    setWindowTitle("Waver");
    this->actionsEnabled(false);
    ui->customPlot->xAxis->setVisible(false);
    ui->customPlot->yAxis->setVisible(false);
    ui->customPlot->removePlottable(0);
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
