#ifndef DIALOG_PACKETRECOVERY_H
#define DIALOG_PACKETRECOVERY_H

#include <QDialog>

namespace Ui {
class Dialog_PacketRecovery;
}

class Dialog_PacketRecovery : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog_PacketRecovery(QWidget *parent = 0);
    ~Dialog_PacketRecovery();

    int getAlgorithm();

private slots:
    void on_buttonBox_accepted();

private:
    int number;
    Ui::Dialog_PacketRecovery *ui;
};

#endif // DIALOG_PACKETRECOVERY_H
