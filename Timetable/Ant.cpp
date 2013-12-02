/* 
 * File:   Ant.cpp
 * Author: heber
 * 
 * Created on 15 de Março de 2013, 01:45
 */

#include "Ant.h"


std::vector<std::vector<double> > Ant::feromoniosT;
std::vector<std::vector<double> >Ant::feromoniosH;
std::vector<std::vector<int> >Ant::bestSol;
double Ant::bestDTF;
double Ant::bestSCP;

Ant::Ant(){
}

void Ant::inicializaSolucao(int numTurmas){
    this->solucao.clear();
    for(int i=0;i<numTurmas;i++){
        this->solucao.push_back(std::vector<int>(5));
    }
}

void Ant::inicializa(Professor *professor, Turma *turmas, int numTurmas){
    feromoniosT.clear();
    feromoniosH.clear();
    bestSol.clear();
    for(int i=0;i<Constantes::getNumeroProf();i++){
        feromoniosT.push_back(std::vector<double>(numTurmas));
        feromoniosH.push_back(std::vector<double>(nh));
    }
    for(int i=0;i<numTurmas;i++){
        bestSol.push_back(std::vector<int>(5));
    }
    for(int i=0;i<Constantes::getNumeroProf();i++){
        for(int j=0; j<numTurmas;j++){
            Ant::feromoniosT[i][j] = 0.3 * professor[i].GetPrefD(turmas[j].indDisc);
        }

        for(int j=0; j<nh;j++){
            Ant::feromoniosH[i][j] = 0.5 * professor[i].GetPrefH(j);
        }
    }
}
