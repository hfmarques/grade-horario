#ifndef SAIDA_H
#define SAIDA_H

#include <QDialog>
#include <QCheckBox>

#include "creditosprofessores.h"
#include "compararesultado.h"
#include "Turma.h"
namespace Ui {
class Saida;
}

class Saida : public QDialog
{
    Q_OBJECT
    
public:
    explicit Saida(QWidget *parent = 0);
    ~Saida();
    
private slots:
    void on_unselectAll_clicked();

    void on_selectAll_clicked();

    void on_credProf_clicked();

    void on_newGrade_clicked();

    void on_comparaResultado_clicked();

private:
    Ui::Saida *ui;
    CreditosProfessores *creditosProf;
    comparaResultado *ComparaResultado;
};

#endif // SAIDA_H
