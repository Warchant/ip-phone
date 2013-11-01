#ifndef DIALOG_PACKETDELETE_H
#define DIALOG_PACKETDELETE_H

#include <QDialog>

namespace Ui {
class Dialog_PacketDelete;
}

class Dialog_PacketDelete : public QDialog
{
    Q_OBJECT
    
public:
    double loss_rate;
    int    packet_length;
    bool   accepted;

    explicit Dialog_PacketDelete(QWidget *parent = 0);
    ~Dialog_PacketDelete();
    
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Dialog_PacketDelete *ui;
};

#endif // DIALOG_PACKETDELETE_H
