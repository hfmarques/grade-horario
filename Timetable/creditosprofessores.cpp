#include "creditosprofessores.h"
#include "ui_creditosprofessores.h"

#include "principal.h"
#include "constantes.h"
#include <iostream>
#include <QTableWidget>
#include <QApplication>
#include <sstream>

CreditosProfessores::CreditosProfessores(QWidget *parent) : QDialog(parent), ui(new Ui::CreditosProfessores)
{
    ui->setupUi(this);
    int row=0;
    for(int a = 0;a < Constantes::getNumeroProf();a++)
    {
        ui->tableWidget->insertRow(row);

        ostringstream convert;

        convert << Principal::professor[a].GetSiap();
        ui->tableWidget->setItem(a,0,new QTableWidgetItem((convert.str().c_str())));
        ui->tableWidget->item(a,0)->setTextAlignment(Qt::AlignHCenter);
        convert.str("");
        convert.clear();

        convert << Principal::professor[a].GetCreditos();
        ui->tableWidget->setItem(a,1,new QTableWidgetItem((convert.str().c_str())));
        ui->tableWidget->item(a,1)->setTextAlignment(Qt::AlignHCenter);
        convert.str("");
        convert.clear();

        convert << Principal::professor[a].GetCargo();
        ui->tableWidget->setItem(a,2,new QTableWidgetItem((convert.str().c_str())));
        ui->tableWidget->item(a,2)->setTextAlignment(Qt::AlignHCenter);
        convert.str("");
        convert.clear();

        row++;
    }
    for(int i=0; i<3;i++)
        ui->tableWidget->setColumnWidth(i, 100);
}

CreditosProfessores::~CreditosProfessores()
{
    delete ui;
}
