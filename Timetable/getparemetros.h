#ifndef GETPAREMETROS_H
#define GETPAREMETROS_H

#include <QDialog>
#include <QString>
#include <constantes.h>


namespace Ui {
class GetParemetros;
}

class GetParemetros : public QDialog
{
    Q_OBJECT
    
public:
    explicit GetParemetros(QWidget *parent = 0);
    ~GetParemetros();
    
private slots:
    void on_buttonBox_accepted();

private:
    Ui::GetParemetros *ui;
};

#endif // GETPAREMETROS_H
