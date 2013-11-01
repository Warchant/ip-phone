#include "dialog_packetdelete.h"
#include "ui_dialog_packetdelete.h"

Dialog_PacketDelete::Dialog_PacketDelete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_PacketDelete)
{
    ui->setupUi(this);
    this->packet_length = 1;
    this->loss_rate     = 0;
    this->accepted      = false;
}

Dialog_PacketDelete::~Dialog_PacketDelete()
{
    delete ui;
}

void Dialog_PacketDelete::on_buttonBox_accepted()
{
    this->packet_length = ui->spinBox_length->value();
    this->loss_rate     = ui->doubleSpinBox_loss_rate->value();
    this->accepted      = true;
}


void Dialog_PacketDelete::on_buttonBox_rejected()
{
    this->packet_length = 1;
    this->loss_rate     = 0;
    this->accepted      = false;
}
