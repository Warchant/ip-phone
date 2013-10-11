#include "dialog_packets.h"
#include "ui_dialog_packets.h"

dialog_packets::dialog_packets(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_packets)
{
    ui->setupUi(this);
    // Create model for tableView
    model = new QStandardItemModel(0,2,this);
    // Set header labels
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Key"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Value"));
    // Set model to tableView
    ui->tableView->setModel(model);
}

dialog_packets::~dialog_packets()
{
    delete ui;
}


