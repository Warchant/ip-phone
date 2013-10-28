#ifndef DIALOG_PACKETS_H
#define DIALOG_PACKETS_H

#include <QDialog>
#include <QTableView>
#include <QStandardItemModel>
#include "tableviewrow.h"

namespace Ui {
class dialog_packets;
}

class dialog_packets : public QDialog
{
    Q_OBJECT
public:
    explicit dialog_packets(QWidget *parent = 0, const tableViewRow *tvr);
    ~dialog_packets();
private:
    Ui::dialog_packets *ui;
    QStandardItemModel *model;

};

#endif // DIALOG_PACKETS_H
