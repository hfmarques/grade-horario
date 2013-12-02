#include <QApplication>
#include "geracaogrades.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GeracaoGrades w;
    w.show();

    return a.exec();
}
