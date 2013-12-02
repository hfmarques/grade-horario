#include "addturma.h"
#include "ui_addturma.h"

#include "Turma.h"
#include "principal.h"
#include <QString>

AddTurma::AddTurma(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTurma)
{
    ui->setupUi(this);
}

AddTurma::~AddTurma()
{
    delete ui;
}

void AddTurma::on_buttonBox_accepted()
{
    Turma *turma = new Turma();
    QString srt = ui->turma->toPlainText();
    const char *toChar = srt.toStdString().c_str();
    turma->codigo[0] = toChar[0];
    turma->codigo[1] = toChar[1];
    turma->codigo[2] = toChar[2];
    srt.clear();

    srt = ui->codigo->toPlainText();
    turma->disc = srt.toInt();

    int i;
    for(i=0;i<Constantes::getNumeroDisc();i++){
        if(turma->disc == Principal::disc.at(i).codigo)
            break;
    }
    if(i>=Constantes::getNumeroDisc()){
        cout<< "erro";
    }

    for(int j=0;i<Constantes::getNumeroProf();j++){
        Principal::professor.at(i).SetPrefD(ui->tableWidget->item(0,i)->text().toInt(), Constantes::getNumeroProf()-1);
    }

    turma->indDisc = i;
    Principal::turmas.push_back(*turma);
    Constantes::setNumeroTurmas(Constantes::getNumeroTurmas()+1);
}

