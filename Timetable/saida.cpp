#include "saida.h"
#include "ui_saida.h"
#include "principal.h"
#include "constantes.h"
#include <iostream>
#include <QTableWidget>
#include <QApplication>
#include <sstream>



Saida::Saida(QWidget *parent):QDialog(parent),ui(new Ui::Saida){
    ui->setupUi(this);

    int row=0;
    int numTurmas = Principal::turmasUtilizadas.size();

    for(int a = 0;a < Principal::solucaoFinal.size();a++)
    {
        ui->tableWidget->insertRow(row);

        ui->tableWidget->setCellWidget(a,0, new QCheckBox(ui->tableWidget));

        ostringstream convert;

        switch(Principal::turmasUtilizadas[Principal::solucaoFinal[a][4]].disc % 10)
        {
            case 0: convert << "DCC";
                break;
            case 1: convert << "EADDCC";
                break;
            default: cout << "\n\nERRO 12\n\n" << endl;
                exit(12);
        }
        if(Principal::turmasUtilizadas[Principal::solucaoFinal[a][4]].disc / 1000 > 0)
            convert << Principal::turmasUtilizadas[Principal::solucaoFinal[a][4]].disc / 10;
        else if(Principal::turmasUtilizadas[Principal::solucaoFinal[a][4]].disc / 100 > 0)
            convert << '0' << Principal::turmasUtilizadas[Principal::solucaoFinal[a][4]].disc / 10;
        else
            convert << "00" << Principal::turmasUtilizadas[Principal::solucaoFinal[a][4]].disc / 10;

        ui->tableWidget->setItem(a,1,new QTableWidgetItem((convert.str().c_str())));
        ui->tableWidget->item(a,1)->setTextAlignment(Qt::AlignHCenter);
        convert.str("");
        convert.clear();


        convert << Principal::disc[Principal::turmasUtilizadas[Principal::solucaoFinal[a][4]].indDisc].nome;
        ui->tableWidget->setItem(a,2,new QTableWidgetItem((convert.str().c_str())));
        convert.str("");
        convert.clear();

        convert << Principal::turmasUtilizadas[Principal::solucaoFinal[a][4]].codigo;
        ui->tableWidget->setItem(a,3,new QTableWidgetItem((convert.str().c_str())));
        ui->tableWidget->item(a,3)->setTextAlignment(Qt::AlignHCenter);
        convert.str("");
        convert.clear();

        convert << 'P' << Ant::getBestSol(a, 0);
        ui->tableWidget->setItem(a,4,new QTableWidgetItem((convert.str().c_str())));
        ui->tableWidget->item(a,4)->setTextAlignment(Qt::AlignHCenter);
        convert.str("");
        convert.clear();


        switch(Ant::getBestSol(a, 1)/15)
        {
            case 0: convert << "SEG ";
                break;
            case 1: convert << "TER ";
                break;
            case 2: convert << "QUA ";
                break;
            case 3: convert << "QUI ";
                break;
            case 4: convert << "SEX ";
                break;
            case 5: convert << "SAB ";
                break;
            default: cout << "\n\nERRO 11\n\n" << endl;
                exit(11);
        }
        convert << (Ant::getBestSol(a, 1)%15)+8 << "h";
        ui->tableWidget->setItem(a,5,new QTableWidgetItem((convert.str().c_str())));
        ui->tableWidget->item(a,5)->setTextAlignment(Qt::AlignHCenter);
        convert.str("");
        convert.clear();

        if(Principal::disc[Ant::getBestSol(a,3)].qtdCreditos==4){
            switch(Ant::getBestSol(a, 2)/15)
            {
                case 0: convert << "SEG ";
                    break;
                case 1: convert << "TER ";
                    break;
                case 2: convert << "QUA ";
                    break;
                case 3: convert << "QUI ";
                    break;
                case 4: convert << "SEX ";
                    break;
                case 5: convert << "SAB ";
                    break;
                default: cout << "\n\nERRO 11\n\n" << endl;
                    exit(11);
            }
            convert << (Ant::getBestSol(a, 2)%15)+8 << "h;";
            ui->tableWidget->setItem(a,6,new QTableWidgetItem((convert.str().c_str())));
            ui->tableWidget->item(a,6)->setTextAlignment(Qt::AlignHCenter);
            convert.str("");
            convert.clear();
        }
        else{
            convert << '-';
            ui->tableWidget->setItem(a,6,new QTableWidgetItem((convert.str().c_str())));
            ui->tableWidget->item(a,6)->setTextAlignment(Qt::AlignHCenter);
            convert.str("");
            convert.clear();
        }
        row++;
    }
    for(int i=0; i<9;i++){
        if(i==0)
            ui->tableWidget->setColumnWidth(i, 22);
        else if(i==2)
            ui->tableWidget->setColumnWidth(i, 430);
        else
            ui->tableWidget->setColumnWidth(i, 83);

    }
}

Saida::~Saida()
{
    delete ui;
}

void Saida::on_unselectAll_clicked()
{
    for(int i=0;i<Constantes::getNumeroTurmas();i++){
        QCheckBox *cb = ((QCheckBox*)ui->tableWidget->cellWidget(i,0));
        cb->setChecked(true);
    }
}

void Saida::on_selectAll_clicked()
{
    for(int i=0;i<Constantes::getNumeroTurmas();i++){
        QCheckBox *cb = ((QCheckBox*)ui->tableWidget->cellWidget(i,0));
        cb->setChecked(false);
    }
}

void Saida::on_credProf_clicked()
{
    creditosProf = new CreditosProfessores(this);
    creditosProf->setWindowFlags(Qt::Window);
    creditosProf->show();
}

void Saida::on_newGrade_clicked()
{
    char *resultado = "/home/heber/Área de Trabalho/Timetable 1.2.0 (Grafic)/Timetable/saida1.csv";
    int numeroTurma = Principal::turmasUtilizadas.size();

    for(int i=0;i<Constantes::getNumeroTurmas();i++){
        QCheckBox *cb = ((QCheckBox*)ui->tableWidget->cellWidget(i,0));
        if(cb->isChecked()){
            numeroTurma--;
        }
    }

    Turma t[numeroTurma];
    int j=0,k=0;
    for(int i=0;i<Principal::turmasUtilizadas.size();i++){
        QCheckBox *cb = ((QCheckBox*)ui->tableWidget->cellWidget(i,0));
        if(!cb->isChecked()){
            t[j] = Principal::turmasUtilizadas.at(i);
            j++;
            Principal::solucaoFinal.erase(Principal::solucaoFinal.begin()+k);
            k--;
        }
        k++;
    }

    Ant::setBestDTF(99999);
    Ant::setBestSCP(99999);
    Principal::run(t, numeroTurma, resultado);

    int row=0;

    for(int a = 0;a < Principal::solucaoFinal.size();a++)
    {
        ui->tableWidget->insertRow(row);

        ui->tableWidget->setCellWidget(a,0, new QCheckBox(ui->tableWidget));

        ostringstream convert;

        switch(Principal::turmasUtilizadas[Principal::solucaoFinal[a][4]].disc % 10)
        {
            case 0: convert << "DCC";
                break;
            case 1: convert << "EADDCC";
                break;
            default: cout << "\n\nERRO 12\n\n" << endl;
                exit(12);
        }
        if(Principal::turmasUtilizadas[Principal::solucaoFinal[a][4]].disc / 1000 > 0)
            convert << Principal::turmasUtilizadas[Principal::solucaoFinal[a][4]].disc / 10;
        else if(Principal::turmasUtilizadas[Principal::solucaoFinal[a][4]].disc / 100 > 0)
            convert << '0' << Principal::turmasUtilizadas[Principal::solucaoFinal[a][4]].disc / 10;
        else
            convert << "00" << Principal::turmasUtilizadas[Principal::solucaoFinal[a][4]].disc / 10;

        ui->tableWidget->setItem(a,1,new QTableWidgetItem((convert.str().c_str())));
        ui->tableWidget->item(a,1)->setTextAlignment(Qt::AlignHCenter);
        convert.str("");
        convert.clear();

        switch(Principal::disc[Principal::turmasUtilizadas[Principal::solucaoFinal[a][4]].indDisc].tipo)
        {
            case 0: convert << "Básica";
                break;
            case 1: convert << "Massa";
                break;
            case 2: convert << "Específica";
                break;
            default: cout << "\n\nERRO 10\n\n" << endl;
        }
        ui->tableWidget->setItem(a,2,new QTableWidgetItem((convert.str().c_str())));
        ui->tableWidget->item(a,2)->setTextAlignment(Qt::AlignHCenter);
        convert.str("");
        convert.clear();

        convert << Principal::disc[Principal::turmasUtilizadas[Principal::solucaoFinal[a][4]].indDisc].nome;
        ui->tableWidget->setItem(a,3,new QTableWidgetItem((convert.str().c_str())));
        convert.str("");
        convert.clear();

        convert << Principal::turmasUtilizadas[Principal::solucaoFinal[a][4]].codigo;
        ui->tableWidget->setItem(a,4,new QTableWidgetItem((convert.str().c_str())));
        ui->tableWidget->item(a,4)->setTextAlignment(Qt::AlignHCenter);
        convert.str("");
        convert.clear();

        convert << 'P' << Ant::getBestSol(a, 0);
        ui->tableWidget->setItem(a,5,new QTableWidgetItem((convert.str().c_str())));
        ui->tableWidget->item(a,5)->setTextAlignment(Qt::AlignHCenter);
        convert.str("");
        convert.clear();

        convert << Principal::disc[Principal::turmasUtilizadas[Principal::solucaoFinal[a][4]].indDisc].qtdCreditos;
        ui->tableWidget->setItem(a,6,new QTableWidgetItem((convert.str().c_str())));
        ui->tableWidget->item(a,6)->setTextAlignment(Qt::AlignHCenter);
        convert.str("");
        convert.clear();

        switch(Ant::getBestSol(a, 1)/18)
        {
            case 0: convert << "SEG ";
                break;
            case 1: convert << "TER ";
                break;
            case 2: convert << "QUA ";
                break;
            case 3: convert << "QUI ";
                break;
            case 4: convert << "SEX ";
                break;
            default: cout << "\n\nERRO 11\n\n" << endl;
                exit(11);
        }
        convert << (Ant::getBestSol(a, 1)%18)+8 << "h";
        ui->tableWidget->setItem(a,7,new QTableWidgetItem((convert.str().c_str())));
        ui->tableWidget->item(a,7)->setTextAlignment(Qt::AlignHCenter);
        convert.str("");
        convert.clear();

        if(Principal::disc[Ant::getBestSol(a,3)].qtdCreditos==4){
            switch(Ant::getBestSol(a, 2)/18)
            {
                case 0: convert << "SEG ";
                    break;
                case 1: convert << "TER ";
                    break;
                case 2: convert << "QUA ";
                    break;
                case 3: convert << "QUI ";
                    break;
                case 4: convert << "SEX ";
                    break;
                default: cout << "\n\nERRO 11\n\n" << endl;
                    exit(11);
            }
            convert << (Ant::getBestSol(a, 2)%18)+8 << "h;";
            ui->tableWidget->setItem(a,8,new QTableWidgetItem((convert.str().c_str())));
            ui->tableWidget->item(a,8)->setTextAlignment(Qt::AlignHCenter);
            convert.str("");
            convert.clear();
        }
        else{
            convert << '-';
            ui->tableWidget->setItem(a,8,new QTableWidgetItem((convert.str().c_str())));
            ui->tableWidget->item(a,8)->setTextAlignment(Qt::AlignHCenter);
            convert.str("");
            convert.clear();
        }
        row++;
    }


}

void Saida::on_comparaResultado_clicked()
{
    ComparaResultado = new comparaResultado(this);
    ComparaResultado->setWindowFlags(Qt::Window);
    ComparaResultado->show();
}
