#include "dialog_noiseinfo.h"
#include "ui_dialog_noiseinfo.h"

Dialog_NoiseInfo::Dialog_NoiseInfo(unsigned char *cData,
                                   const unsigned char *oData,
                                   int size,
                                   QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_NoiseInfo),
    nc(0),cq(0),mse(0),snr(0)
{
    ui->setupUi(this);

    this->currentData  = cData;
    this->originalData = oData;
    this->size         = size;

    this->nc  = calcNc();
    this->cq  = calcCq();
    this->mse = calcMse();
    this->snr = calcSnr();

    this->ui->label_nc->setText( "NC  = " + QString::number(this->nc));
    this->ui->label_cq->setText( "CQ  = " + QString::number(this->cq));
    this->ui->label_mse->setText("MSE = " + QString::number(this->mse));
    this->ui->label_snr->setText("SNR = " + QString::number(this->snr));

}

Dialog_NoiseInfo::~Dialog_NoiseInfo()
{
    delete ui;
}


double Dialog_NoiseInfo::calcNc()
{
    double num = 0;
    double den = 0;
    for(int i=0; i<size; i++)
    {
        num+= (currentData[i]==0?1:currentData[i]) * (originalData[i]==0?1:originalData[i]);
        den+= (currentData[i]==0?1:currentData[i]) * (currentData[i]==0?1:currentData[i]);
    }
    return num/den;
}


double Dialog_NoiseInfo::calcCq()
{
    double num = 0;
    double den = 0;
    for(int i=0; i<size; i++)
    {
        num+= (currentData[i]==0?1:currentData[i]) * (originalData[i]==0?1:originalData[i]);
        den+= (currentData[i]==0?1:currentData[i]);
    }
    return num/den;
}


double Dialog_NoiseInfo::calcMse()
{
    double sum = 0;
    for(int i=0; i<size; i++)
    {
        int el = (currentData[i]==0?1:currentData[i]) - (originalData[i]==0?1:originalData[i]);
        sum+= el*el;
    }
    return sum/this->size;
}


double Dialog_NoiseInfo::calcSnr()
{
    return 0;
}
