#ifndef DIALOG_RECORD_H
#define DIALOG_RECORD_H

#include <QDialog>
#include <QStringList>
#include <QString>
#include "wav.h"

namespace Ui {
class Dialog_Record;
}

class Dialog_Record : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog_Record(QWidget *parent = 0);
    ~Dialog_Record();
    
    int getBps() const;
    int getSampleRate() const;
    int getChannels() const;

    WAV* getWav();

private slots:
    void on_buttonBox_accepted();

private:
    int bps;
    int sampleRate;
    int channels;

    void setBps(int value);
    void setSampleRate(int value);
    void setChannels(int value);

    WAV *wav;

    Ui::Dialog_Record *ui;
};

#endif // DIALOG_RECORD_H
