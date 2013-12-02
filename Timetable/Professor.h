/* 
 * File:   Professor.h
 * Author: heber
 *
 * Created on 18 de Março de 2013, 14:43
 */

#ifndef PROFESSOR_H
#define	PROFESSOR_H
#include <iostream>
#include <vector>
#include <cstdlib>

class Professor
{
    public:
    int GetCargo(){
        return cargo;
    }

    void SetCargo(int cargo) {
        this->cargo = cargo;
    }

    int GetCredMax(){
        return credMax;
    }

    void SetCredMax(int credMax) {
        this->credMax = credMax;
    }

    int GetCreditos(){
        return creditos;
    }

    void SetCreditos(int creditos) {
        this->creditos = creditos;
    }

    int GetPrefD(int i){
        if(i<130){
            return prefD[i];
        }
        exit(9);
        std::cout<<"ERRO 09"<<std::endl;
    }

    void SetPrefD(int prefD[130]) {
        for(int i=0;i<130;i++)
            this->prefD[i] = prefD[i];
    }
    
    void SetPrefD(int prefD, int i) {
        int size = this->prefD.size();
        if(i==size){
            this->prefD.push_back(prefD);
            return;
        }
        else if(i>size){
            for(int j=size;j<=i;j++){
                this->prefD.push_back(-1);
            }
        }
        this->prefD[i] = prefD;
    }

    int GetPrefH(int i){
        return prefH[i];
    }

    void SetPrefH(int prefH, int i) {
        int size = this->prefH.size();
        if(i==size){
            this->prefH.push_back(prefH);
            return;
        }
        else if(i>size){
            for(int j=size;j<=i;j++){
                this->prefH.push_back(0);
            }
        }
        this->prefH[i] = prefH;
    }

    int GetSiap(){
        return siap;
    }

    void SetSiap(int siap) {
        this->siap = siap;
    }
    

    protected:
    private:
        std::vector<int> prefD; // preferencia de disciplinas
        std::vector<int> prefH; // preferencia de horarios
        int credMax;
        int siap;
        int creditos;
        int cargo;
};

#endif	/* PROFESSOR_H */

