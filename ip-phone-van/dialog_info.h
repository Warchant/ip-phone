#ifndef DIALOG_INFO_H
#define DIALOG_INFO_H

#include <QDialog>
#include <QString>
#include <map>
#include <string>
#include <algorithm>

namespace Ui {
class Dialog_Info;
}

class Dialog_Info : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog_Info(std::map<std::string, std::string> wav, QWidget *parent = 0);
    ~Dialog_Info();
    
private:
    Ui::Dialog_Info *ui;
};

#endif // DIALOG_INFO_H
