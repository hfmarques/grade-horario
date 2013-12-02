#include "compararesultado.h"
#include "ui_compararesultado.h"

#define tam 100

comparaResultado::comparaResultado(QWidget *parent) : QDialog(parent), ui(new Ui::comparaResultado)
{
    ui->setupUi(this);

    char *arq1 = "/home/heber/Área de Trabalho/Timetable 1.2.0 (Grafic)/Timetable/saida2.csv";

    char read[tam];

    ifstream arqi(arq1);

    if(arqi.fail())
    {
        cout << "\n\nERRO ao gerar as comparaçoes de soluçoes\n\n" << endl;
        exit(1);
    }

    int row=0;

    arqi.get(read,tam,';');

    for(int a = 0;strcmp(read,"") != 0;a++)
    {
        int celulaAtual = 0;
        ostringstream convert;

        ui->tableWidget->insertRow(row);

        ui->tableWidget->setItem(celulaAtual,0,new QTableWidgetItem(read));
        ui->tableWidget->item(celulaAtual,0)->setTextAlignment(Qt::AlignHCenter);


        arqi.get();
        arqi.get(read,tam,';');

        ui->tableWidget->setItem(celulaAtual,1,new QTableWidgetItem(read));
        ui->tableWidget->item(celulaAtual,1)->setTextAlignment(Qt::AlignHCenter);

        arqi.get();
        arqi.get(read,tam,';');

        ui->tableWidget->setItem(celulaAtual,2,new QTableWidgetItem(read));
        ui->tableWidget->item(celulaAtual,2)->setTextAlignment(Qt::AlignHCenter);

        row++;
        celulaAtual++;
    }

    arqi.close();
}

comparaResultado::~comparaResultado()
{
    delete ui;
}
