#ifndef DIALOG_NOISEINFO_H
#define DIALOG_NOISEINFO_H

#include <QDialog>

#include "functions.h"

namespace Ui {
class Dialog_NoiseInfo;
}

class Dialog_NoiseInfo : public QDialog
{
    Q_OBJECT
    
public:
    Dialog_NoiseInfo(packet *cData,
                     const packet *oData,
                     int size,
                     QWidget *parent = 0);
    ~Dialog_NoiseInfo();

    double calcNc();
    double calcCq();
    double calcMse();
    double calcSnr();

private:
    Ui::Dialog_NoiseInfo *ui;

    /**
     * @brief nc Normalized Cross-Correlation
     */
    double nc;
    /**
     * @brief cq Correlation quality
     */
    double cq;
    /**
     * @brief mse Mean-square error
     */
    double mse;
    /**
     * @brief snr Signal-noise ratio
     */
    double snr;

    int size;
    packet * currentData;
    const packet * originalData;
};

#endif // DIALOG_NOISEINFO_H
