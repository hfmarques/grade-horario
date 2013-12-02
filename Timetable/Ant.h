/*
 * File:   Ant.h
 * Author: heber
 *
 * Created on 15 de Março de 2013, 01:45
 */

#ifndef ANT_H
#define	ANT_H

#include <vector>
#include "Professor.h"
#include "Turma.h"
#include "constantes.h"

#define ndia 5 // numero de dias
#define nh 90 // numero de horas
#define e 1 // tolerancia minima de feromonios


class Ant
{
    public:

        Ant();
        
        double getDTF(){
            return DTF;
        }

        void setDTF(double DTF) {
            this->DTF = DTF;
        }

        double getSCP(){
            return SCP;
        }

        void setSCP(double SCP) {
            this->SCP = SCP;
        }
        
        static double getFeromoniosH(int i, int j){
            return feromoniosH[i][j];
        }

        static void setFeromoniosH(double feromonios, int i, int j) {
            int size = feromoniosH.size();
            if(i==size){
                std::vector<double>row(nh);
                feromoniosH.push_back(row);
                feromoniosH[i][j] = feromonios;
                return;
            }
            int sizeRow = feromoniosH.at(i).size();
            size = feromoniosH.size();
            if(i<size && sizeRow==j){
                feromoniosH.at(i).push_back(feromonios);
                feromoniosH[i][j] = feromonios;
                return;
            }
            else if(i>size){
                for(int j=size;j<=i;j++){
                    std::vector<double>row(nh);
                    feromoniosH.push_back(row);
                }
            }
            else if(j>sizeRow){
                for(int j=size;j<=i;j++){
                    feromoniosH.at(i).push_back(0);
                }
            }
            feromoniosH[i][j] = feromonios;
        }

        static double getFeromoniosT(int i, int j){
            return feromoniosT[i][j];
        }

        static void setFeromoniosT(double feromonios, int i, int j) {
            int size = feromoniosT.size();
            if(i==size){
                std::vector<double>row(Constantes::getNumeroTurmas());
                feromoniosT.push_back(row);
                feromoniosT[i][j] = feromonios;
                return;
            }
            int sizeRow = feromoniosT.at(i).size();
            size = feromoniosT.size();
            if(i<size && sizeRow==j){
                feromoniosT.at(i).push_back(feromonios);
                feromoniosT[i][j] = feromonios;
                return;
            }
            else if(i>size){
                for(int j=size;j<=i;j++){
                    std::vector<double>row(Constantes::getNumeroTurmas());
                    feromoniosT.push_back(row);
                }
            }
            else if(j>sizeRow){
                for(int j=size;j<=i;j++){
                    feromoniosT.at(i).push_back(0);
                }
            }
            feromoniosT[i][j] = feromonios;
        }

        std::vector<std::vector<int> > getSolucao(){
            return solucao;
        }

        std::vector<std::vector<int> > getBestSol(){
            return bestSol;
        }

        int getSolucao(int i, int j){
            return solucao[i][j];
        }

        void setSolucao(int solucao, int i, int j) {
            int size = this->solucao.size();
            if(i==size){
                std::vector<int>row(4);
                this->solucao.push_back(row);
                this->solucao[i][j] = solucao;
                return;
            }
            else if(i>size){
                for(int j=size;j<=i;j++){
                    std::vector<int>row(4);
                    this->solucao.push_back(row);
                }
            }
            this->solucao[i][j] = solucao;
        }

        static int getBestSol(int i, int j){
            return bestSol[i][j];
        }
        
        static void setBestSol(int BestSol, int i, int j) {
            int size = bestSol.size();
            if(i==size){
                std::vector<int>row(4);
                bestSol.push_back(row);
                bestSol[i][j] = BestSol;
                return;
            }
            else if(i>size){
                for(int j=size;j<=i;j++){
                    std::vector<int>row(4);
                    bestSol.push_back(row);
                }
            }
            bestSol[i][j] = BestSol;
        }
        
        static double getBestDTF(){
            return bestDTF;
        }

        static void setBestDTF(double BestDTF) {
            bestDTF = BestDTF;
        }

        static double getBestSCP() {
            return bestSCP;
        }

        static void setBestSCP(double BestSCP) {
            bestSCP = BestSCP;
        }
        
        static void inicializa(Professor *professor, Turma *turmas,int);
        void inicializaSolucao(int numTurmas);
        

    protected:
    private:
        
        std::vector<std::vector<int> >solucao; // turmas definidas pelo indice, professor indice 0, horario 1 indice 1, horario 1 indice 2(caso nao tenha  = -1), 3 indice daquela turma no vetor de disciplinas, 4 indice da turma
        double DTF;
        double SCP;
        static double bestDTF;
        static double bestSCP;
        static std::vector<std::vector<double> >feromoniosT;
        static std::vector<std::vector<double> >feromoniosH;
        static std::vector<std::vector<int> >bestSol; // melhor solução encontrada até o momento
        int sequeciaT[113];
};

#endif	/* ANT_H */

