#include "geracaogrades.h"
#include "ui_geracaogrades.h"
#include "principal.h"
#include "constantes.h"
#include <iostream>
#include <QTableWidget>
#include <QApplication>
#include <sstream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

GeracaoGrades::GeracaoGrades(QWidget *parent) : QMainWindow(parent), ui(new Ui::GeracaoGrades)
{
    ui->setupUi(this);
}

GeracaoGrades::~GeracaoGrades()
{
    delete ui;
}



void GeracaoGrades::on_carregarPlanilias_clicked()
{

//    getParametros = new GetParemetros();
//    getParametros->setWindowFlags(Qt::Window);
//    getParametros->show();



    char *arq1 = "/home/heber/Copy/Bolsa/GETComp/Timetable 1.2.0 (Grafic)/Timetable/entrada.csv";
    char *arq2 = "/home/heber/Copy/Bolsa/GETComp/Timetable 1.2.0 (Grafic)/Timetable/entrada2.csv";
    char *arq3 = "/home/heber/Copy/Bolsa/GETComp/Timetable 1.2.0 (Grafic)/Timetable/entrada3.csv";
    Principal::leituraArquivo(arq1,arq2,arq3);
    Principal::inicializaHoras();


    int row=0;
    for(int a = 0;a < Constantes::getNumeroTurmas();a++)
    {
        ui->tableWidget->insertRow(row);

        ui->tableWidget->setCellWidget(a,0, new QCheckBox(ui->tableWidget));

        ostringstream convert;
        convert << Principal::turmas[a].disc / 10;
        ui->tableWidget->setItem(a,1,new QTableWidgetItem((convert.str()).c_str()));
        ui->tableWidget->item(a,1)->setTextAlignment(Qt::AlignHCenter);
        convert.str("");
        convert.clear();

        switch(Principal::disc[Principal::turmas[a].indDisc].tipo){
                case 0: ui->tableWidget->setItem(a,2,new QTableWidgetItem("Basica"));
                break;
                case 1: ui->tableWidget->setItem(a,2,new QTableWidgetItem("Massa"));
                break;
                case 2: ui->tableWidget->setItem(a,2,new QTableWidgetItem("Especifica"));
                break;
                default: cout << "\n\nERRO 10\n\n" << endl;
        }
        ui->tableWidget->item(a,2)->setTextAlignment(Qt::AlignHCenter);

        ui->tableWidget->setItem(a,3,new QTableWidgetItem((Principal::disc[Principal::turmas[a].indDisc].nome).c_str()));

        convert << Principal::turmas[a].codigo;
        ui->tableWidget->setItem(a,4,new QTableWidgetItem((convert.str()).c_str()));
        ui->tableWidget->item(a,4)->setTextAlignment(Qt::AlignHCenter);
        convert.str("");
        convert.clear();

        convert << Principal::disc[Principal::turmas[a].indDisc].qtdCreditos;
        ui->tableWidget->setItem(a,5,new QTableWidgetItem((convert.str()).c_str()));
        ui->tableWidget->item(a,5)->setTextAlignment(Qt::AlignHCenter);
        convert.str("");
        convert.clear();

        row++;
    }
    for(int i=0; i<6;i++){
        if(i==0)
            ui->tableWidget->setColumnWidth(i, 22);
        else if(i==2)
            ui->tableWidget->setColumnWidth(i, 100);
        else if(i==3)
            ui->tableWidget->setColumnWidth(i, 430);
        else
            ui->tableWidget->setColumnWidth(i, 65);

    }
    for(int i=0;i<Constantes::getNumeroTurmas();i++){
        QCheckBox *cb = ((QCheckBox*)ui->tableWidget->cellWidget(i,0));
        cb->setChecked(true);
    }

}

void GeracaoGrades::on_gerarGrades_clicked()
{
    int numeroTurma=0;
    char resultado[300] = "/home/heber/Área de Trabalho/Timetable 1.2.0 (Grafic)/Timetable/saida2.csv";
    srand(time(NULL));

    for(int i=0;i<Constantes::getNumeroTurmas();i++){
        QCheckBox *cb = ((QCheckBox*)ui->tableWidget->cellWidget(i,0));
        if(cb->isChecked()){
            Principal::turmasUtilizadas.push_back(Principal::turmas.at(i));
            numeroTurma++;
        }
    }

    Turma t[numeroTurma];
    for(int i=0;i<numeroTurma;i++){
        t[i]= Principal::turmasUtilizadas.at(i);
    }
    Principal::run(t, numeroTurma, resultado);
}

void GeracaoGrades::on_gerarSaida_clicked()
{
    char end[300] = "/home/heber/Área de Trabalho/Timetable 1.2.0 (Grafic)/Timetable/saida1.csv";
    Principal::gerarSaida(end);

    saida = new Saida(this);
    saida->setWindowFlags(Qt::Window);
    saida->show();
}


void GeracaoGrades::on_addTurma_clicked()
{
    addTurma = new AddTurma(this);
    addTurma->setWindowFlags(Qt::Window);
    addTurma->show();
}

void GeracaoGrades::on_selectAll_clicked()
{
    for(int i=0;i<Constantes::getNumeroTurmas();i++){
        QCheckBox *cb = ((QCheckBox*)ui->tableWidget->cellWidget(i,0));
        cb->setChecked(true);
    }
}

void GeracaoGrades::on_unselectAll_clicked()
{
    for(int i=0;i<Constantes::getNumeroTurmas();i++){
        QCheckBox *cb = ((QCheckBox*)ui->tableWidget->cellWidget(i,0));
        cb->setChecked(false);
    }
}
