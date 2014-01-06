/* 
 * File:   operacoes.cpp
 * Author: heber
 *
 * Created on 18 de Março de 2013, 14:41
 */

#include "Ant.h"
#include "operacoes.h"
#include "Disciplina.h"
#include "constantes.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <cmath>




int operacoes::convert(char *str){
    int num = 0, a = 0;
    int size = strlen(str);
    if(str[a] == '-')
        a++;
    for(;a < size;a++)
    {
        switch(str[a])
        {
            case '1': num += 1 * pow(10,size-a-1);
                break;
            case '2': num += 2 * pow(10,size-a-1);
                break;
            case '3': num += 3 * pow(10,size-a-1);
                break;
            case '4': num += 4 * pow(10,size-a-1);
                break;
            case '5': num += 5 * pow(10,size-a-1);
                break;
            case '6': num += 6 * pow(10,size-a-1);
                break;
            case '7': num += 7 * pow(10,size-a-1);
                break;
            case '8': num += 8 * pow(10,size-a-1);
                break;
            case '9': num += 9 * pow(10,size-a-1);
                break;
            case '0': break;
            default: std::cout << "\n\nERRO 01\n\n" << str << std::endl;
                exit(1);
        }
    }
    if(str[a] == '-')
        return (-num);
    return (num);
}

int operacoes::posT=0;
int operacoes::posH=0;
int operacoes::posH2=0;

void operacoes::getNextPermItemT(double w[][2], int j, int tamanhoVetor){
    
    double o=0, rnd=0, m;
    int q;
    
    
    for(int k=j;k<tamanhoVetor;k++){
        o=o+w[k][0];
    }

    if(j>=posT){
        for(int k=posT;k<=j;k++){
            if(o>e){
                rnd=o*((double)rand() / RAND_MAX)+0.1;
                q=posT;
                m=0;
                while(m<rnd && q<tamanhoVetor){
                    m=m+w[q][0];
                    q++;
                }

                o=o-w[q-1][0];
                swap(w, q-1,k);
            }
            else{
                swap(w, rand()%(posT - k + 1) + k, k); // gera numeros randomicos entre pos e k
            }

            posT++;
        }
    }
}


void operacoes::getNextPermItemH(double w[][2], int j, int tamanhoVetor){
    
    double o=0, rnd=0, m;
    int q;
    
    
    for(int k=j;k<tamanhoVetor;k++){
        o=o+w[k][0];
    }

    if(j>=posH){
        for(int k=posH;k<=j;k++){
            if(o>e){
                rnd=o*((double)rand() / RAND_MAX)+0.1;
                q=posH;
                m=0;
                while(m<rnd && q<tamanhoVetor){
                    m=m+w[q][0];
                    q++;
                }
                
                o=o-w[q-1][0];
                swap(w, q-1,k);
            }
            else{
                swap(w, rand()%(posH - k + 1) + k, k); // gera numeros randomicos entre pos e k
            }

            posH++;
        }
    }
}


void operacoes::getNextPermItemH2(double w[][2], int j, int tamanhoVetor){
    
    double o=0, rnd=0, m;
    int q;
    
    for(int k=j;k<tamanhoVetor;k++){
        o=o+w[k][0];
    }

    if(j>=posH2){
        for(int k=posH2;k<=j;k++){
            if(o>e){
                rnd=o*((double)rand() / RAND_MAX)+0.1;
                q=posH2;
                m=0;
                while(m<rnd && q<tamanhoVetor){
                    m=m+w[q][0];
                    q++;
                }
                
                o=o-w[q-1][0];
                swap(w, q-1,k);
            }
            else{
                swap(w, rand()%(posH2 - k + 1) + k, k); // gera numeros randomicos entre pos e k
            }

            posH2++;
        }
    }
}

void operacoes::swap(double w[][2], int i, int j){
    double k = w[i][0];
    w[i][0] = w[j][0];
    w[j][0] = k;
    k = w[i][1];
    w[i][1] = w[j][1];
    w[j][1] = k;
}

bool operacoes::validasolucao(Ant ant, Professor prof, int horario, int horario2, int nt){
//    if(horario == horario2){
//        return false;
//    }

    int aux[1000], j=0;

    for(int i=0;i<1000;i++)
        aux[i]=-1;

    for(int i=0; i<nt; i++){ // varre todo o vetor de solução buscando a hora de todas as aulas do professor
        if(prof.GetSiap() == ant.getSolucao(i,0)){ // achando ele salva seus horarios em um vetor auxiliar
            if(j>1000){
                std::cout<<"erro 7"<<std::endl;
                exit(7);
            }

            if(aux[j]!= -1){
                aux[j] = ant.getSolucao(i,1);
                j++;
            }

            if(aux[j]!=-1){
                aux[j] = ant.getSolucao(i,2);
                j++;
            }
        }
    }

    for(int i=0;i<j; i++){ // verifica se há horarios conflitantes
        if(aux[i] == horario || (aux[i]<horario && (aux[i]+2)>horario) || (horario<aux[i] && (horario+2)>aux[i]))
            return false; // se conflitaram horarios nao deixa construir
        if(aux[i] == horario2 || (aux[i]<horario2 && (aux[i]+2)>horario2) || (horario2<aux[i] && (horario2+2)>aux[i]))
            return false; // se conflitaram horarios nao deixa construir
    }
    return true;
}


double operacoes::classificaHC(Ant ant, Professor *prof, Disciplina *disc, int nt, int np){
    double pontuacao = 0;
    int creditos = 0;
    for(int j=0;j<nt;j++){ // verifica se há aulas com preferencia menos que 2
        if(prof[ant.getSolucao(j,0)].GetPrefD(ant.getSolucao(j,3))<2 && disc[ant.getSolucao(j,3)].tipo != 0){
            pontuacao = pontuacao + 1;
        }
    }


    for(int i=0;i<np;i++){
        for(int j=0;j<nt;j++){
            if(i==ant.getSolucao(j,0)){
                creditos = creditos + disc[ant.getSolucao(j,3)].qtdCreditos;
            }
        }

        creditos += prof[i].GetCreditos();

        if(prof[i].GetCargo()==0 && creditos>8){ // verifica se há chefes de departamento com mais de 8 creditos
            pontuacao = pontuacao + 1;
        }

        else if(creditos<8 || creditos>16){
            pontuacao = pontuacao + 1;
        }

        creditos = 0;
    }

    return pontuacao;
}

double operacoes::classificaSC(Ant ant, Professor *prof, int nt, int np){
    double pontuacao = 0;

    for(int i=0;i<nt;i++){ // prof nao deve dar disciplina de pref diferente de 3
        if(prof[ant.getSolucao(i,0)].GetPrefD(ant.getSolucao(i,3))!=3){
            pontuacao = pontuacao + 0.01;
        }

    }


    for(int i=0;i<nt; i++){ //prof nao deve dar aulas em horarios inadequados
        if(prof[ant.getSolucao(i,0)].GetPrefH(ant.getSolucao(i,1))!=1){
            pontuacao = pontuacao + 0.1;
        }
        if(prof[ant.getSolucao(i,0)].GetPrefH(ant.getSolucao(i,2))!=1 && prof[ant.getSolucao(i,0)].GetPrefH(ant.getSolucao(i,2))!=-1){
            pontuacao = pontuacao + 0.1;
        }
    }

//    int aux[1000], j=0; // professor nao deve dar 2 aulas seguidas

//    for(int m=0;m<np;m++){
//        for(int z=0;z<1000;z++)
//           aux[z] = -1;

//        for(int i=0; i<nt; i++){ // varre todo o vetor de solução buscando a hora de todas as aulas do professor
//            if(prof[ant.getSolucao(m,0)].GetSiap() == ant.getSolucao(i,0)){ // achando ele salva seus horarios em um vetor auxiliar
//                if(j>1000){
//                    std::cout<<"erro 8"<<std::endl;
//                    exit(8);
//                }

//                if(aux[j]!= -1){
//                    aux[j] = ant.getSolucao(i,1);
//                    j++;
//                }

//                if(aux[j]!=-1){
//                    aux[j] = ant.getSolucao(i,2);
//                    j++;
//                }
//            }
//        }

//        for(int i=0;i<j; i++){ // verifica se há aulas seguidas
//            for(int k=i+1;k<j;k++){
//                if(aux[i]+2 == aux[j] || aux[j]+2 == aux[i]){
//                    pontuacao = pontuacao + 0.01;
//                }
//            }
//        }
//        j=0;
//    }

    return pontuacao;
}

double operacoes::classificaBestHC(Ant ant, Professor *prof, Disciplina *disc, int nt, int np){
    double pontuacao = 0;
    int creditos = 0;
    for(int j=0;j<nt;j++){ // verifica se há aulas com preferencia menos que 2
        if(prof[ant.getBestSol(j,0)].GetPrefD(ant.getBestSol(j,3))<2 && disc[ant.getBestSol(j,3)].tipo != 0){
            pontuacao = pontuacao + 1;
        }
    }

    for(int i=0;i<np;i++){
        for(int j=0;j<nt;j++){
            if(i==ant.getBestSol(j,0)){
                creditos = creditos + disc[ant.getBestSol(j,3)].qtdCreditos;
            }
        }

        creditos += prof[i].GetCreditos();

        if(prof[i].GetCargo()==0 && creditos>8){ // verifica se há chefes de departamento com mais de 8 creditos
            pontuacao = pontuacao + 1;
        }

        else if(creditos<8 || creditos>16){
            pontuacao = pontuacao + 1;
        }
        creditos = 0;

    }

    return pontuacao;
}

double operacoes::classificaBestSC(Ant ant, Professor *prof, int nt, int np){
    double pontuacao = 0;

    for(int i=0;i<nt;i++){ // prof nao deve dar disciplina de pref diferente de 3
        if(prof[ant.getBestSol(i,0)].GetPrefD(ant.getBestSol(i,3))!=3){
            pontuacao = pontuacao + 0.01;
        }

    }

    for(int i=0;i<nt; i++){ //prof nao deve dar aulas em horarios inadequados
        if(prof[ant.getBestSol(i,0)].GetPrefH(ant.getBestSol(i,1))!=1){
            pontuacao = pontuacao + 0.1;
        }
        if(prof[ant.getBestSol(i,0)].GetPrefH(ant.getBestSol(i,2))!=1 && prof[ant.getBestSol(i,0)].GetPrefH(ant.getBestSol(i,2))!=-1){
            pontuacao = pontuacao + 0.1;
        }
    }

//    int aux[1000], j=0; // professor nao deve dar 2 aulas seguidas

//    for(int m=0;m<np;m++){
//        for(int z=0;z<100;z++)
//           aux[z] = 0;

//        for(int i=0; i<nt; i++){ // varre todo o vetor de solução buscando a hora de todas as aulas do professor
//            if(prof[ant.getBestSol(m,0)].GetSiap() == ant.getBestSol(i,0)){ // achando ele salva seus horarios em um vetor auxiliar
//                if(j>1000){
//                    std::cout<<"erro 8"<<std::endl;
//                    exit(8);
//                }

//                if(aux[j]!= -1){
//                    aux[j] = ant.getSolucao(i,1);
//                    j++;
//                }

//                if(aux[j]!=-1){
//                    aux[j] = ant.getSolucao(i,2);
//                    j++;
//                }
//            }
//        }

//        for(int i=0;i<j; i++){ // verifica se há aulas seguidas
//            for(int k=i+1;k<j;k++){
//                if(aux[i]+2 == aux[j] || aux[j]+2 == aux[i]){
//                    pontuacao = pontuacao + 0.01;
//                }

//            }

//        }
//        j=0;
//    }

    return pontuacao;
}




double operacoes::classificaElementoSC(Ant ant, Professor prof, int posicao, int nt){
    int pontuacao = 0;
    bool hahorario = false;

    // prof nao deve dar disciplina de pref diferente de 3
    if(prof.GetPrefD(ant.getSolucao(posicao,3))!=3){
        pontuacao = pontuacao + 0.01;
    }

    //prof nao deve dar aulas em horarios inadequados
    if(prof.GetPrefH(ant.getSolucao(posicao,1))!=1){
        pontuacao = pontuacao + 0.1;
    }
    if(prof.GetPrefH(ant.getSolucao(posicao,2))!=1 && prof.GetPrefH(ant.getSolucao(posicao,2))!=-1){
        pontuacao = pontuacao + 0.1;
    }

//    int aux[1000], j=0; // professor nao deve dar 2 aulas seguidas
//    aux[0] = ant.getSolucao(posicao,0);
//    for(int i=0; i<nt; i++){ // varre todo o vetor de solução buscando a hora de todas as aulas do professor
//        if(i != posicao && prof.GetSiap() == ant.getSolucao(i,0)){ // achando ele salva seus horarios em um vetor auxiliar
//            if(j>1000){
//                std::cout<<"erro 8"<<std::endl;
//                exit(8);
//            }

//            if(aux[j]!= -1){
//                aux[j] = ant.getSolucao(i,1);
//                j++;
//            }

//            if(aux[j]!=-1){
//                aux[j] = ant.getSolucao(i,2);
//                j++;
//            }
//        }
//    }

//    for(int i=0;i<j; i++){ // verifica se há aulas seguidas
//        if(aux[i]+2 == aux[0] || aux[0]+2 == aux[i]){
//           pontuacao = pontuacao + 0.01;
//        }
//    }
    return pontuacao;
}


bool operacoes::compareBestSol(Ant a){

    for(int i=0;i<Constantes::getNumeroTurmas();i++){
        for(int j=0;j<4;j++){
            if(a.getBestSol(i,j) != a.getSolucao(i,j)){
                return false;
            }
        }
    }
    
    return true;
    
}
