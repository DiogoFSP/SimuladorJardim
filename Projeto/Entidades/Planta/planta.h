#ifndef PLANTA_H
#define PLANTA_H

#include <iostream>
#include <ostream>
#include <string>

#include "../../Solo/solo.h"
class Solo;

class Planta {
private:
    std::string beleza;
    char simbolo;
    float agua;
    float nutrientes;

    bool nascagr;
    int idade;

public:
    Planta(int aguaInicial, int nutrientesInicial, const std::string &beleza, char simbolo);

    virtual ~Planta();

    float getAgua() const;

    int getNutrientes() const;

    char getSimbolo() const;

    std::string getBeleza() const;

    void addagua(float qtd);

    void rmvagua(float qtd);

    void setAgua(float agua);

    void addnutrientes(float qtd);

    void rmvnutrientes(float qtd);

    void setNutri (float nutrientes);

    bool nasceuAgora() const;
    void setNascagr(bool nascagr);
    int getIdade() const;

    virtual void absagua(Solo& s) = 0; //obriga que seja a subclase a subescrever
    virtual void absnutrientes(Solo& s) = 0; //obriga que seja a subclase a subescrever
    virtual bool morre(Solo& s, Solo* vizinhos[8])=0; //obriga que seja a subclase a subescrever
    virtual void multiplica(Solo& s, Solo* vizinhos[8]) = 0; //obriga que seja a subclase a subescrever
    virtual void processa(Solo& s, Solo* vizinhos[8]);

};

#endif
