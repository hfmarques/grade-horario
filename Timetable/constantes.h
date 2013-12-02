#ifndef CONSTANTES_H
#define CONSTANTES_H

class Constantes
{
public:
    Constantes();

    static int getNumeroProf(){
        return numeroProf;
    }

    static void setNumeroProf(int np){
        numeroProf = np;
    }

    static int getNumeroDisc(){
        return numeroDisc;
    }

    static void setNumeroDisc(int nd){
        numeroDisc = nd;
    }

    static int getNumeroTurmas(){
        return numeroTurmas;
    }

    static void setNumeroTurmas(int nt){
        numeroTurmas = nt;
    }

private:
    static int numeroProf; // Número de professores
    static int numeroDisc; //Número de disciplinas
    static int numeroTurmas; // Número de turmas
};

#endif // CONSTANTES_H
