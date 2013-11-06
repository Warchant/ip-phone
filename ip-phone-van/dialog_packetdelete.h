#ifndef DIALOG_PACKETDELETE_H
#define DIALOG_PACKETDELETE_H

#include <QDialog>
#include <QObject>
#include <QString>
#include "functions.h"

namespace Ui {
class Dialog_PacketDelete;
}

class Dialog_PacketDelete : public QDialog
{
    Q_OBJECT
    
public:
    int    to_delete;
    int    packet_length;

    explicit Dialog_PacketDelete(int length,QWidget *parent = 0);
    ~Dialog_PacketDelete();
    
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_sb_length_editingFinished();

private:

    Ui::Dialog_PacketDelete *ui;

    const int m_length;
};

#endif // DIALOG_PACKETDELETE_H
