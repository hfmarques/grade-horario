#ifndef CREDITOSPROFESSORES_H
#define CREDITOSPROFESSORES_H

#include <QDialog>


namespace Ui {
class CreditosProfessores;
}

class CreditosProfessores : public QDialog
{
    Q_OBJECT
    
public:
    explicit CreditosProfessores(QWidget *parent = 0);
    ~CreditosProfessores();
    
private:
    Ui::CreditosProfessores *ui;
};

#endif // CREDITOSPROFESSORES_H
