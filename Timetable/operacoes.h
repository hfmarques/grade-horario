/* 
 * File:   operacoes.h
 * Author: heber
 *
 * Created on 18 de Março de 2013, 14:41
 */

#ifndef OPERACOES_H
#define	OPERACOES_H

#include <vector>

#include "Disciplina.h"

class operacoes
{
    public: //lembrete passar uma formiga no erro
        
        static int convert(char *str);
        static void getNextPermItemT(double w[][2], int j, int tamanhoVetor);
        static void getNextPermItemH(double w[][2], int j, int tamanhoVetor);
        static void getNextPermItemH2(double w[][2], int j, int tamanhoVetor, int horario);
        static bool validasolucao(Ant ant, Professor prof, int horario, int horario2, int nt); // verifica se um professor está dando duas aulas no mesmo horario
        static double classificaHC(Ant ant, Professor *prof, Disciplina *disc, int nt, int np);
        static double classificaSC(Ant ant, Professor *prof, int nt, int np);
        static double classificaBestHC(Ant ant, Professor *prof, Disciplina *disc, int nt, int np);
        static double classificaBestSC(Ant ant, Professor *prof, int nt, int np);
        static double classificaElementoSC(Ant ant, Professor prof, int posicao, int nt);
        static bool compareBestSol(Ant);
        static void setPosT(int p) {
            posT = p;
        }
        static int getPosT(){
            return posT;
        }
        static void setPosH(int p) {
            posH = p;
        }
        static int getPosH(){
            return posH;
        }
        static void setPosH2(int p) {
            posH2 = p;
        }
        static int getPosH2(){
            return posH2;
        }
        
    protected:
    private:

       static int posH; // posição para turmas
       static int posH2; // posição para turmas
       static int posT; // posição para horarios
       static void swap(double w[][2], int i, int j);
};

#endif	/* OPERACOES_H */

