#ifndef PRINCIPAL_H
#define PRINCIPAL_H
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <vector>
#include "Disciplina.h"
#include "Professor.h"
#include "Horario.h"
#include "Ant.h"
#include "Turma.h"
#include "operacoes.h"
#include "constantes.h"

#define na 50 // numero de formigas
#define ndia 5 // numero de dias
#define nh 90 // numero de horas
#define tam 100 // Tamanho do vetor de leitura
#define ign 10000 // Qtd de caracteres a ignorar
#define imax 5000 // Máximo de iterações
#define y 0.1 // fator de penalidade
#define p 0.1 // fator de evaporação dos feromonios
#define w 0.8 // variavel omega que define o quanto será a normalização dos feromonios
#define controlSolFreeze 500 // controla quando uma solução otima é encontrada varias vezes consecultivas
#define controlBestSolFreeze 1500 // controla quando uma solução otima é encontrada varias vezes consecultivas

using namespace std;

typedef struct Solucoes{
    int formigas;
    double DFT;
    double SCP;
}solucoes;

class Principal
{
private:


public:
    static vector<Professor> professor; // vetor de professores a serem lidos na tabela
    static vector<Turma> turmas; // vetor de turmas a ser lido na tabela
    static vector<Turma> turmasUtilizadas; // vetor de turmas selecionado pelo usuario para gerar a soluçao
    static Horario horario[nh][ndia]; // vetor de horarios a ser lido na tabela
    static vector<Disciplina> disc; // vetor de disciplina a ser lido na tabela
    static Ant formigas[na]; // vetor de formigas
    static vector<vector<int> > solucaoFinal; // vetor que armazena a soluçao final encontrada


    Principal();
    static void leituraArquivo(char*,char*,char*);
    static void run(Turma turma[], int numeroTurma, char*);
    static void gerarSaida(char*);
    static void inicializaHoras();
};

#endif // PRINCIPAL_H
