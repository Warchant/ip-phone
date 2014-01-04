#include "dialog_packetdelete.h"
#include "ui_dialog_packetdelete.h"

Dialog_PacketDelete::Dialog_PacketDelete(int length, QWidget *parent) :
    m_length(length),QDialog(parent),
    ui(new Ui::Dialog_PacketDelete)
{
    ui->setupUi(this);
    ui->sb_length  ->setMaximum(m_length);
    ui->sb_todelete->setMaximum(m_length);
    ui->sb_todelete->setSuffix (tr(" из ") + int2str(m_length).c_str());
}


Dialog_PacketDelete::~Dialog_PacketDelete()
{
    delete ui;
}


void Dialog_PacketDelete::on_buttonBox_accepted()
{
    on_sb_length_editingFinished();
    this->packet_length = ui->sb_length->value();
    this->to_delete     = ui->sb_todelete->value();
}


void Dialog_PacketDelete::on_buttonBox_rejected()
{
    this->packet_length = 1;
    this->to_delete     = 0;
}


void Dialog_PacketDelete::on_sb_length_editingFinished()
{
    int val = ui->sb_length->value();
    // if number of bytes is bigger than 30 000
    val     = val > 30000 ? 5000 : val;
    if(m_length % 2 != 0)
    {
        m_length--;
    }
    if(m_length % val != 0)
    {
        ui->sb_length->setValue(val < m_length/2 + 1 ? val - 1 : val + 1);
        on_sb_length_editingFinished();
    }
    else
    {
        int newMax = m_length/val;
        ui->sb_todelete->setSuffix(tr(" из ") + int2str(newMax).c_str());
        ui->sb_todelete->setMaximum(newMax);
        return;
    }
}
