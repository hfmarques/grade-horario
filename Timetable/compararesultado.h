#ifndef COMPARARESULTADO_H
#define COMPARARESULTADO_H

#include <QDialog>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstring>

using namespace std;

namespace Ui {
class comparaResultado;
}

class comparaResultado : public QDialog
{
    Q_OBJECT
    
public:
    explicit comparaResultado(QWidget *parent = 0);
    ~comparaResultado();
    
private:
    Ui::comparaResultado *ui;
};

#endif // COMPARARESULTADO_H
