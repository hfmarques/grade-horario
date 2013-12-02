#ifndef GERACAOGRADES_H
#define GERACAOGRADES_H

#include <QMainWindow>
#include <QCheckBox>
#include "addturma.h"
#include "saida.h"
#include "getparemetros.h"
#include <vector>


namespace Ui {
class GeracaoGrades;
}

class GeracaoGrades : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit GeracaoGrades(QWidget *parent = 0);
    ~GeracaoGrades();
    
private slots:

    void on_carregarPlanilias_clicked();

    void on_gerarSaida_clicked();

    void on_gerarGrades_clicked();

    void on_addTurma_clicked();

    void on_selectAll_clicked();

    void on_unselectAll_clicked();

private:
    Ui::GeracaoGrades *ui;
    AddTurma *addTurma;
    Saida *saida;
    GetParemetros *getParametros;

};

#endif // GERACAOGRADES_H
