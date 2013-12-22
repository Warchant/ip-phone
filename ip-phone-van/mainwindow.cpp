#include "mainwindow.h"
#include "ui_mainwindow.h"

#define PLACEHOLDER 1
#define STOP_SYMBOL 0

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

    this->algorithms   = new RepairAlgorithm(0);
    this->packetLength = 0;
}


MainWindow::~MainWindow()
{
    delete algorithms;
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

    const QCPDataMap *dataMap = ui->customPlot->graph(0)->data();
    QVector <double> y;
    for(QMap<double, QCPData>::const_iterator it = dataMap->constBegin();
        it!=dataMap->constEnd(); ++it)
    {
        y.push_back(it.value().value);
    }

    for(int i=0; i<size; i++)
    {
        min = min > y.at(i) ? y.at(i) : min;
        max = max < y.at(i) ? y.at(i) : max;
    }

    // Set ranges to top and bottom axis
    ui->customPlot->yAxis->setRange(min <= 2?2:min, max);
    ui->customPlot->xAxis->setRange(0, time);
    ui->customPlot->setInteractions( QCP::iRangeDrag | QCP::iRangeZoom );
    ui->customPlot->axisRect(0)->setRangeDrag(Qt::Horizontal);
    ui->customPlot->axisRect(0)->setRangeZoom(Qt::Horizontal);
    ui->customPlot->xAxis->setLabel("Time, ms");
    ui->customPlot->yAxis->setLabel("Quantization Level");
    ui->customPlot->setNoAntialiasingOnDrag(true);
    ui->customPlot->xAxis->setVisible(true);
    ui->customPlot->yAxis->setVisible(true);
}

void MainWindow::plotReplot()
{
    std::vector <int> empty;
    this->plotReplot(empty);
}


void MainWindow::plotReplot(std::vector <int> index_ignore)
{
    std::map <std::string, std::string> wav = file->wav_header->getHeader();
    int     bps = wav.empty()?0: str2int(wav["bitsPerSample"]);
    int    size = wav.empty()?0: str2int(wav["subChunk2Size"]);
    double time = double(size) / bps;

    unsigned char * data = file->wav_header->data;

    QVector<double> x(size), y(size);
    for (int i=0; i<size; i++)
    {
        x[i] = time*(double(i)/(size-1));
        y[i] = double(data[i]);
    }

    if(!index_ignore.empty())
    {
        for (unsigned int i=0; i<index_ignore.size();i++ )
        {
            for(int j=0; j<this->packetLength; j++)
            {
                int index = index_ignore[i]*this->packetLength + j;
                y[index] = PLACEHOLDER ;
            }
        }
    }

    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x,y);
    this->plotSetup();
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
    ui->action_noiseinfo->setDisabled(!state);
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
    rnd.resize(amount>length?length:amount);
    return rnd;
}


bool MainWindow::saveFile(QString path)
{
    QFile f(path);

    if (!f.open(QIODevice::ReadWrite))
        return false;

    if(f.seek(file->wav_header->getHeaderSize()))
    {
        f.write((const char*)file->wav_header->data, sizeinbytes);
    }
    else
    {
        return false;
    }
    f.close();
    return true;
}


void MainWindow::on_action_open_triggered()
{
    try
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
            file->setPath( path );
            this->plotReplot();
            setWindowTitle("Waver (" + path + ")");
            this->actionsEnabled(true);

            delete this->algorithms;
            std::map<std::string,std::string> wav = file->wav_header->getHeader();
            this->sizeinbytes = str2int(wav["subChunk2Size"]);
            int size = str2int(wav["subChunk2Size"]);
            this->algorithms = new RepairAlgorithm(size);
            this->algorithms->setData(file->wav_header->data);
        }
    }
    catch (WAV::EXCEPTION e)
    {
        switch(e)
        {
        case WAV::FILE_BAD_HEADER:
        {
            // bad header
            QMessageBox warning;
            warning.setText(tr("Не удалось распознать формат файла. Неправильный заголовок."));
            warning.exec();
            exit(1);
        }break;
        case WAV::FILE_DATA_LOAD_FAIL:
        {
            // data load fail
            QMessageBox warning;
            warning.setText(tr("Не удалось прочесть данные файла. Возможно, файл имеет неправильный формат."));
            warning.exec();
            exit(2);
        }break;
        case WAV::FILE_MISSING:
        {
            // file is missing
            QMessageBox warning;
            warning.setText(tr("Не удалось открыть файл. Файл отсутствует."));
            warning.exec();
            exit(3);
        }break;
        case WAV::FILE_HEADER_NOT8BPS:
        {
            // file is missing
            QMessageBox warning;
            warning.setText(tr("Не удалось открыть файл. Поддерживаются только 8-битные WAV файлы."));
            warning.exec();
            exit(4);
        }break;
        }
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
    Dialog_PacketDelete *dpd = new Dialog_PacketDelete(sizeinbytes,this);

    if(dpd->exec()) //show dialog
    {
        this->packetLength = dpd->packet_length;
        int size           = sizeinbytes/this->packetLength;   // size of new array: data divided into packets

        algorithms->setPacketsAmount(size);
        algorithms->container->createPackets(this->packetLength); // create packets from bytes

        if(dpd->to_delete > 0)
        {
            del_index = randVector(1,size,dpd->to_delete);
            this->plotReplot(del_index);
            const QCPDataMap *dataMap = ui->customPlot->graph(0)->data();
            QVector <double> y;
            for(QMap<double, QCPData>::const_iterator it = dataMap->constBegin();
                it!=dataMap->constEnd(); ++it)
            {
                y.push_back(it.value().value);
            }
            file->wav_header->convert2data(y);
        }

        if(dpd->to_delete > 0)
        {
            setWindowTitle(windowTitle().remove("*"));
            setWindowTitle(windowTitle() + "*");
        }
    }
    delete dpd;

    // backup data with deleted packets
    memcpy(algorithms->container->data_del,algorithms->container->data,sizeinbytes);
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
    ui->customPlot->replot();
}


void MainWindow::on_action_save_triggered()
{
    setWindowTitle(windowTitle().remove("*"));
    if(!this->saveFile(file->getPath()))
    {
        QMessageBox warning;
        warning.setText(tr("Не удалось сохранить файл. Возможно, нет доступа к папке."));
        warning.exec();
    }
}


void MainWindow::on_action_playpause_triggered()
{
    if(file->isOpen())
        file->pausePlayback();
    file->startPlayback();
}


void MainWindow::on_action_stop_triggered()
{
    ui->action_playpause->setChecked(false);
    if(file->isOpen())
    {
        file->stopPlayback();
    }
}

void MainWindow::on_action_packetRecover_triggered()
{
    if(this->packetLength == 0)
    {
        std::map<std::string,std::string> wav = file->wav_header->getHeader();

        if(wav.empty())
            return;

        this->sizeinbytes = str2int(wav["subChunk2Size"]);

        // calculate packet length
        std::vector <int> lengths;
        int k = 0;
        lengths.push_back(0);
        for(int i=0; i<sizeinbytes; i++)
        {
            if(file->wav_header->data[i] == PLACEHOLDER)
            {
                lengths[k]++;
            }
            else
            {
                lengths.push_back(0);
                k++;
            }
        }

        lengths.erase(
                    std::remove_if(lengths.begin(),
                                   lengths.end(),
                                   [](int el){return el<=1;}
        ), lengths.end());

        std::for_each(lengths.begin(),lengths.end(),[&](int el){printf("%i\t",el);});
        this->packetLength = *std::min_element(lengths.begin(),lengths.end());
        this->packetLength = this->packetLength == 0 ? 1 : this->packetLength;

        // create packets
        algorithms->setPacketsAmount(sizeinbytes/this->packetLength);
        algorithms->container->createPackets(this->packetLength); // create packets from bytes
    }

    Dialog_PacketRecovery *dpr = new Dialog_PacketRecovery(this);
    if(dpr->exec())
    {
        switch(dpr->getAlgorithm())
        {
            case 1:
                memcpy(file->wav_header->data,file->wav_header->getOriginalData(),sizeinbytes); break;
            case 0:
                memcpy(algorithms->container->data,algorithms->container->data_del,sizeinbytes); break;
            case 2:
                algorithms->splicing(); break;
            case 3:
                algorithms->silenceSubstitution(); break;
            case 4:
                algorithms->noiseSubstitution(); break;
            case 5:
                algorithms->packetRepetition(); break;
            case 6:
                algorithms->timeScaleModification(); break;
        }
        this->plotReplot();
    }
    delete dpr;
}


void MainWindow::on_action_saveas_triggered()
{
    QFileDialog *fdi = new QFileDialog(this);
    fdi->setNameFilter(tr("WAV files (*.wav)"));
    fdi->setAcceptMode(QFileDialog::AcceptSave);
    if(fdi->exec())
    {
        QString path = fdi->selectedFiles().at(0);
        file->copyFileTo(path);
        if(!this->saveFile(path))
        {
            QMessageBox warning;
            warning.setText(tr("Не удалось сохранить файл. Возможно, нет доступа к папке."));
            warning.exec();
        }
        setWindowTitle("Waver (" + path + ")");
    }
}


void MainWindow::on_action_noiseinfo_triggered()
{
    std::map<std::string,std::string> wav = file->wav_header->getHeader();

    if(wav.empty())
        return;

    Dialog_NoiseInfo *dni = new Dialog_NoiseInfo(file->wav_header->data,
                                                 file->wav_header->getOriginalData(),
                                                 sizeinbytes,
                                                 this);
    dni->exec();
    delete dni;
}
