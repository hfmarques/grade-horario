/* 
 * File:   Disciplina.h
 * Author: heber
 *
 * Created on 18 de Março de 2013, 14:42
 */

#ifndef DISCIPLINA_H
#define	DISCIPLINA_H

#include <iostream>

class Disciplina
{
    public:

        std::string nome;
        int codigo;
        int qtdCreditos;
        int tipo; // 1,2,3
        int area;
        bool horarioFixo; // se a disciplina possue horario fixo ou nao

    protected:
    private:
};

#endif	/* DISCIPLINA_H */

