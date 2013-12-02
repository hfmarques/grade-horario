#include "getparemetros.h"
#include "ui_getparemetros.h"

GetParemetros::GetParemetros(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GetParemetros)
{
    ui->setupUi(this);
}

GetParemetros::~GetParemetros()
{
    delete ui;
}

void GetParemetros::on_buttonBox_accepted()
{
    bool ok;
    QString str = ui->numProf->toPlainText();
    Constantes::setNumeroProf(str.toInt(&ok, 10));
    str.clear();

    str = ui->numTurmas->toPlainText();
    Constantes::setNumeroTurmas(str.toInt(&ok, 10));
    str.clear();

    str = ui->numDisc->toPlainText();
    Constantes::setNumeroDisc(str.toInt(&ok, 10));
    str.clear();

}
