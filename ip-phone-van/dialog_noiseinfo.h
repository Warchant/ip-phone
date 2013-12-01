#ifndef DIALOG_NOISEINFO_H
#define DIALOG_NOISEINFO_H

#include <QDialog>

namespace Ui {
class Dialog_NoiseInfo;
}

class Dialog_NoiseInfo : public QDialog
{
    Q_OBJECT
    
public:
    Dialog_NoiseInfo(unsigned char *cData,
                     const unsigned char *oData,
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
    unsigned char * currentData;
    const unsigned char * originalData;
};

#endif // DIALOG_NOISEINFO_H
