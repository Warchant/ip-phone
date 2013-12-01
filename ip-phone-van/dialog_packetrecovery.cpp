#include "dialog_packetrecovery.h"
#include "ui_dialog_packetrecovery.h"

Dialog_PacketRecovery::Dialog_PacketRecovery(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_PacketRecovery)
{
    ui->setupUi(this);

    QStringList itemList;
    itemList << "<Restore the original>"
             << "<Restore the deletion>"
             << "Splicing"
             << "Silence Substitution"
             << "Noise Substitution"
             << "Packet Repetition";
    ui->comboBox_algo->addItems(itemList);
    number = 0;
}


Dialog_PacketRecovery::~Dialog_PacketRecovery()
{
    delete ui;
}


int Dialog_PacketRecovery::getAlgorithm()
{
    return this->number;
}


void Dialog_PacketRecovery::on_buttonBox_accepted()
{
    this->number = ui->comboBox_algo->currentIndex();
}
