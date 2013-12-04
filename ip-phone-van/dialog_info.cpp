#include "dialog_info.h"
#include "ui_dialog_info.h"

Dialog_Info::Dialog_Info(std::map<std::string, std::string> wav, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Info)
{
    ui->setupUi(this);

    int row = 0;
    for(std::map<std::string, std::string>::iterator it = wav.begin(); it != wav.end(); ++it)
    {
        QTableWidgetItem *key = new QTableWidgetItem(tr("%1").arg( ((*it).first).c_str() ) );
        ui->table_info->setItem(row, 0, key);

        QString s = ((*it).second).c_str();
        QTableWidgetItem *val = new QTableWidgetItem(tr("%1").arg(s) );
        ui->table_info->setItem(row, 1, val);

        row++;
    }
}

Dialog_Info::~Dialog_Info()
{
    delete ui;
}
