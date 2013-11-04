#include "dialog_record.h"
#include "ui_dialog_record.h"

Dialog_Record::Dialog_Record(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Record)
{
    ui->setupUi(this);

    QStringList channels;
    channels << "Mono" << "Stereo";
    ui->cb_channels->addItems(channels);
    ui->cb_channels->setDisabled(true);

    QStringList bps;
    bps << "8" << "16";
    ui->cb_bps->addItems(bps);

    QStringList sampleRate;
    sampleRate << "8000" << "11025" << "22050" << "44100";
    ui->cb_sampleRate->addItems(sampleRate);
}


WAV *Dialog_Record::getWav()
{
    return this->wav;
}


Dialog_Record::~Dialog_Record()
{
    delete ui;
}


int Dialog_Record::getChannels() const
{
    return channels;
}

void Dialog_Record::setChannels(int value)
{
    switch(value)
    {
        case 0: this->channels = 1; break;
        case 1: this->channels = 2; break;
        default: printf("problem with channel\n");
    }
}


int Dialog_Record::getSampleRate() const
{
    return sampleRate;
}


void Dialog_Record::setSampleRate(int value)
{
    switch(value)
    {
        case 0: this->sampleRate = 8000; break;
        case 1: this->sampleRate = 11025; break;
        case 2: this->sampleRate = 22050; break;
        case 3: this->sampleRate = 44100; break;
        default: printf("problem with sampleRate\n");
    }
}


int Dialog_Record::getBps() const
{
    return bps;
}


void Dialog_Record::setBps(int value)
{
    switch(value)
    {
        case 0: this->bps = 8; break;
        case 1: this->bps = 16; break;
        default: printf("problem with sampleRate\n");
    }
}


void Dialog_Record::on_buttonBox_accepted()
{
    setBps(ui->cb_bps->currentIndex());
    setChannels(ui->cb_channels->currentIndex());
    setSampleRate(ui->cb_sampleRate->currentIndex());
}
