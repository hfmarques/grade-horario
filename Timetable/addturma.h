#ifndef ADDTURMA_H
#define ADDTURMA_H

#include <QDialog>


namespace Ui {
class AddTurma;
}

class AddTurma : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddTurma(QWidget *parent = 0);
    ~AddTurma();
    
private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddTurma *ui;
};

#endif // ADDTURMA_H
